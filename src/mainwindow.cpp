/**************************************************************************
*   Copyright (C) 2011 by Matteo Agostinelli                              *
*   agostinelli@gmail.com                                                 *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.          *
***************************************************************************/

#include "mainwindow.h"
#include "cirkuitsettings.h"
#include "circuitmacrosmanager.h"
#include "generatorthread.h"

#include "ui_cirkuit_general_settings.h"

#include "lib/document.h"
#include "lib/backend.h"
#include "lib/format.h"
#include "lib/generator.h"
#include "lib/documenttemplate.h"

#include "widgets/previewwidget.h"
#include "widgets/imageview.h"
#include "widgets/logviewwidget.h"
#include "widgets/backendchoosedialog.h"
#include "widgets/templatechoosedialog.h"

#include <KApplication>
#include <KAction>
#include <KToggleAction>
#include <KLocale>
#include <KActionCollection>
#include <KStandardAction>
#include <KStandardDirs>
#include <KRecentFilesAction>
#include <KFileDialog>
#include <KShortcutsDialog>
#include <KMessageBox>
#include <KIO/NetAccess>
#include <KSaveFile>
#include <KMenu>
#include <QTextStream>
#include <QListWidget>
#include <QFileInfo>
#include <QFileSystemModel>
#include <QTimer>
#include <KXMLGUIFactory>
#include <KConfigDialog>
#include <KStatusBar>
#include <KRun>
#include <KProcess>
#include <kmimetypetrader.h>
#include <KConfigSkeletonItem>

#include <knewstuff3/downloaddialog.h>
#include <knewstuff3/uploaddialog.h>

#include <KTextEditor/Document>
#include <KTextEditor/View>
#include <KTextEditor/Editor>
#include <KTextEditor/EditorChooser>

MainWindow::MainWindow(QWidget *)
{
    KTextEditor::Editor *editor = KTextEditor::EditorChooser::editor();

    if (!editor) {
        KMessageBox::error(this, i18n("A KDE text-editor component could not be found;\n"
        "please check your KDE installation."));
        kapp->exit(1);
    }

    m_doc = (Cirkuit::Document*) (editor->createDocument(0));
    m_doc->initialize();
    m_view = qobject_cast<KTextEditor::View*>(m_doc->createView(this));
   
    m_previewWidget = new PreviewWidget(i18n("Preview"), this);
    m_previewWidget->setObjectName("preview-dock");
    m_imageView = m_previewWidget->view();
    addDockWidget(Qt::TopDockWidgetArea, m_previewWidget);
    
    m_logViewWidget = new LogViewWidget(i18n("Log"), this);
    m_logViewWidget->setObjectName("log-dock");
    addDockWidget(Qt::BottomDockWidgetArea, m_logViewWidget);
    m_logViewWidget->hide();

    mimeTypes << "application/x-cirkuit" << "text/x-tex" << "application/x-gnuplot";
    m_currentFile = KUrl("");
    updateTitle();

    setCentralWidget(m_view);
    setAutoSaveSettings();
    setupActions();

    setXMLFile("cirkuitui.rc");
    createShellGUI(true);
    substituteSaveAsAction();

    guiFactory()->addClient(m_view);
    m_view->setContextMenu(qobject_cast<KMenu *> (factory()->container("ktexteditor_popup", this)));

    m_generator = new GeneratorThread;
    
    m_updateTimer = 0;
    updateConfiguration();
    statusBar()->showMessage(i18n("Ready"), 3000);
    
    connect(m_generator, SIGNAL(success()), this, SLOT(builtNotification()));
    connect(m_generator, SIGNAL(fail()), this, SLOT(failedNotification()));
    connect(m_doc, SIGNAL(modifiedChanged(KTextEditor::Document*)), this, SLOT(documentModified(KTextEditor::Document*)));

    connect(m_generator, SIGNAL(previewReady(QImage)), this, SLOT(showPreview(QImage)));
    connect(m_generator, SIGNAL(fileReady(QString)), this, SLOT(saveFileToDisk(QString)));
    connect(m_generator, SIGNAL(error(QString,QString)), m_logViewWidget, SLOT(displayError(QString,QString)));
    connect(m_generator, SIGNAL(output(QString,QString)), m_logViewWidget, SLOT(displayMessage(QString,QString)));   
    connect(m_generator, SIGNAL(previewUrl(QString)), m_imageView, SLOT(setPdfUrl(QString)));
    connect(m_generator, SIGNAL(backendChanged(QString)), this, SLOT(backendChanged(QString)));
    
    checkCircuitMacros();
    initializeBackend();
    newDocument();
}

void MainWindow::setupActions()
{
	KStandardAction::openNew(this, SLOT(newFile()), actionCollection());
    KStandardAction::quit(this, SLOT(close()), actionCollection());
    KStandardAction::open(this, SLOT(openFile()), actionCollection());
    KStandardAction::save(this, SLOT(save()), actionCollection());
    KStandardAction::saveAs(this, SLOT(saveAs()), actionCollection());
    KStandardAction::close(this, SLOT(newDocument()), actionCollection());
    KStandardAction::clear(this, SLOT(clear()), actionCollection());
    KStandardAction::preferences(this, SLOT(configure()), actionCollection());    
    KStandardAction::keyBindings(this, SLOT(configureKeyBindings()), actionCollection());
    KStandardAction::configureToolbars(this, SLOT(configureToolbars()), actionCollection());
                                            
    recentFilesAction = KStandardAction::openRecent(this, SLOT(loadFile(KUrl)),
                                                                    actionCollection());
                                                                    
    KAction* exportAction = new KAction(KIcon("document-export"), i18n("Export..."), 0);
    actionCollection()->addAction("export", exportAction);
    connect(exportAction, SIGNAL(triggered()), this, SLOT(exportFile()));

    KAction* buildPreviewAction = new KAction(i18n("Build preview"), 0);
    buildPreviewAction->setShortcut(Qt::ALT + Qt::Key_1);
    buildPreviewAction->setIcon(KIcon("run-build"));
    actionCollection()->addAction("build_preview", buildPreviewAction);
    connect(buildPreviewAction, SIGNAL(triggered()), this, SLOT(buildPreview()));

    KAction* openPreviewAction = new KAction(i18n("Open preview"), 0);
    openPreviewAction->setShortcut(Qt::ALT + Qt::Key_2);
    openPreviewAction->setIcon(KIcon("document-preview"));
    actionCollection()->addAction("open_preview", openPreviewAction);
    connect(openPreviewAction, SIGNAL(triggered()), this, SLOT(openPreview()));
    
    KAction* templateManagerAction = new KAction(i18n("Template manager"), 0);
    actionCollection()->addAction("template_manager", templateManagerAction);
    connect(templateManagerAction, SIGNAL(triggered()), this, SLOT(openTemplateManager()));

    KAction* showManualAction = new KAction(KIcon("help-contents"), i18n("Show manual"),0);
    actionCollection()->addAction( "showManual", showManualAction );
    connect(showManualAction, SIGNAL(triggered()), this, SLOT(showManual()));

    KAction* showExamplesAction = new KAction(i18n("Show examples"),0);
    actionCollection()->addAction( "showExamples", showExamplesAction );
    connect(showExamplesAction, SIGNAL(triggered()), this, SLOT(showExamples()));

    QAction* showLivePreviewAction = m_previewWidget->toggleViewAction();
    showLivePreviewAction->setIcon(KIcon("document-preview"));
    actionCollection()->addAction( "show_live_preview", showLivePreviewAction );

    KAction* downloadExamples = new KAction(i18n("Download Examples"), actionCollection());
    downloadExamples->setIcon(KIcon("get-hot-new-stuff"));
    actionCollection()->addAction("download_examples",  downloadExamples);
    connect(downloadExamples, SIGNAL(triggered()), this,  SLOT(downloadExamples()));
    
    KAction* uploadExample = new KAction(i18n("Upload Example"), actionCollection());
    uploadExample->setIcon(KIcon("get-hot-new-stuff"));
    actionCollection()->addAction("upload_example",  uploadExample);
    connect(uploadExample, SIGNAL(triggered()), this,  SLOT(uploadExample()));
    
    KAction* openExample =new KAction(i18n("&Open Example"), actionCollection());
    openExample->setIcon(KIcon("document-open"));
    actionCollection()->addAction("file_open_example", openExample);
    connect(openExample, SIGNAL(triggered()), this, SLOT(openExample()));    
    
    QAction* showLogViewAction = m_logViewWidget->toggleViewAction();
    actionCollection()->addAction( "show_log_view", showLogViewAction );
    showLogViewAction->setIcon(KIcon("documentation"));

    KConfig *config = CirkuitSettings::self()->config();
    recentFilesAction->loadEntries(config->group("recent_files"));

    m_imageView->setupActions(actionCollection());
    m_imageView->zoomFitPageAction()->setChecked(CirkuitSettings::zoomToFit());
    m_imageView->updateZoomToFit();
}

void MainWindow::substituteSaveAsAction()
{
    foreach (QAction* action, m_view->actionCollection()->actions()) {
        if (action->text().contains("Save")) {
            m_view->actionCollection()->removeAction(action);
        }
    }
}

void MainWindow::clear()
{
    m_doc->clear();
}

void MainWindow::newFile()
{
    QPointer<BackendChooseDialog> dlg = new BackendChooseDialog(CirkuitSettings::defaultBackend(), this);
    
    connect(dlg, SIGNAL(backendSelected(QString)), this, SLOT(newDocument(QString)));
    connect(dlg, SIGNAL(defaultBackendSelected(QString)), this, SLOT(setDefaultBackend(QString)));
    
    dlg->exec();
    delete dlg;
}

void MainWindow::openFile()
{
    QString filename;

    QPointer<KFileDialog> openFileDialog = new KFileDialog(KUrl(), "", this);
    openFileDialog->setWindowTitle(i18n("Open file - Cirkuit"));
    openFileDialog->setOperationMode(KFileDialog::Opening);
    openFileDialog->setMimeFilter(mimeTypes);
    if (openFileDialog->exec() == QDialog::Accepted) {
        filename = openFileDialog->selectedFile();
    }

    if (!filename.isEmpty()) {
        m_imageView->clear();
        recentFilesAction->addUrl(KUrl(filename));
        loadFile(filename);
    }
}

void MainWindow::loadFile(const KUrl& url)
{
    m_currentFile = url;
    m_view->document()->openUrl(url);
    m_imageView->clear();
    m_firstRun = true;
    m_backend = Cirkuit::Backend::autoChooseBackend(m_doc);
    buildPreview();
    updateTitle();
}

void MainWindow::save()
{
    if (m_currentFile.isEmpty()) {
        saveAs();
        return;
    }

    m_doc->save();
    if (CirkuitSettings::refreshOnSave()) {
        buildPreview();
    }
}

void MainWindow::saveAs()
{
    QString filename;

    QPointer<KFileDialog> saveFileDialog = new KFileDialog(KUrl(), "", this);
    saveFileDialog->setWindowTitle(i18n("Save file - Cirkuit"));
    saveFileDialog->setOperationMode(KFileDialog::Saving);
    saveFileDialog->setMimeFilter(mimeTypes, "application/x-cirkuit");
    saveFileDialog->setConfirmOverwrite(true);
    if (saveFileDialog->exec() == QDialog::Accepted) {
        filename = saveFileDialog->selectedFile();
    }

    if (!filename.isEmpty()) {
        saveAsFile(filename);
    }
}

void MainWindow::saveAsFile(const KUrl& url)
{
    if (CirkuitSettings::refreshOnSave()) {
        buildPreview();
    }
    m_doc->saveAs(url);
    recentFilesAction->addUrl(url);
    m_currentFile = url.fileName();
    updateTitle();
}

void MainWindow::exportFile()
{
    QString path;

    QStringList exportTypes;
    exportTypes << "application/pdf" << "image/x-eps" << "image/png" << "image/jpeg" << "image/svg+xml" << "image/gif" << "text/x-tex";

    QPointer<KFileDialog> saveFileDialog = new KFileDialog(KUrl(), "", this);
    saveFileDialog->setWindowTitle(i18n("Export image - Cirkuit"));
    saveFileDialog->setStartDir(m_currentFile.directory());
    saveFileDialog->setOperationMode(KFileDialog::Saving);
    saveFileDialog->setMimeFilter(exportTypes, "application/pdf");
    saveFileDialog->setInlinePreviewShown(true);
    saveFileDialog->setConfirmOverwrite(true);
    if (saveFileDialog->exec() == QDialog::Accepted) {
        path = saveFileDialog->selectedFile();
    }

    if (!path.isEmpty()) {
        QFileInfo fileinfo(path);
        Cirkuit::Format format = Cirkuit::Format::fromMimeType(saveFileDialog->currentFilterMimeType());
        statusBar()->showMessage("Exporting image...");
        m_generator->generate(Cirkuit::Format::Source, format, m_backend, m_doc, true);
        m_tempSavePath = path;
        QFile oldFile(path);
        oldFile.remove();
    }
}

void MainWindow::documentModified(KTextEditor::Document* doc)
{
    setWindowModified(doc->isModified());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    KConfig *config = CirkuitSettings::self()->config();
    recentFilesAction->saveEntries(config->group("recent_files"));
    
    CirkuitSettings::setZoomToFit(m_imageView->zoomFitPageAction()->isChecked());
    CirkuitSettings::self()->writeConfig();

    if (!m_doc->closeUrl()) {
        event->ignore();
    } else {
        event->accept();
    }
}

void MainWindow::buildPreview()
{
    if (m_updateTimer) {
        m_updateTimer->stop();
    }
    statusBar()->showMessage("Building preview...");
    m_logViewWidget->clear();
    m_logViewWidget->hide();
    
    m_generator->generate(Cirkuit::Format::Source, Cirkuit::Format::QtImage, m_backend, m_doc, false, m_imageView->scaleFactor());
    
    kDebug() << "Preview generation in progress...";
}

void MainWindow::openPreview()
{
    connect(m_generator, SIGNAL(finished()), this, SLOT(openPreviewFile()));
    
    buildPreview();
}

void MainWindow::openPreviewFile()
{
    disconnect(m_generator, SIGNAL(finished()), this, SLOT(openPreviewFile()));
    
    KUrl url = m_generator->previewUrl();
    if (!url.isLocalFile()) {    
        return;
    }
    
    KRun::runUrl(url, "application/pdf", this);
}

void MainWindow::builtNotification()
{
    statusBar()->showMessage(i18n("Preview built"), 3000);
}

void MainWindow::newDocument(const QString& backendName)
{
    if (!backendName.isEmpty()) {
        Cirkuit::Backend* newBackend = Cirkuit::Backend::getBackend(backendName);
        if (!newBackend) {
            KMessageBox::error(this, i18n("Backend %1 not found", backendName));
            return;
        } else {
            m_backend = newBackend;
            backendChanged(m_backend->name());
        }
    }
    
    if (!m_backend) {
        KMessageBox::error(this, i18n("No valid backend selected."));
        return;
    }
    
    m_doc->applySettings(m_backend->documentSettings());
    if (!m_doc->closeUrl()) {
        return;
    }
    reset();
    
    m_doc->setText(m_doc->initialText());
    KTextEditor::Cursor cursor = m_view->cursorPosition();
    cursor.setLine(m_doc->initialLineNumber());
    m_view->setCursorPosition(cursor);
    m_doc->setModified(false);
}

void MainWindow::updateTitle()
{
    m_windowTitle = "Cirkuit";

    if (!m_currentFile.isEmpty()) {
        m_windowTitle += " - " + m_currentFile.fileName();
    }
    
    m_windowTitle += "[*]";
    setWindowTitle(m_windowTitle);
}

void MainWindow::reset()
{
    m_currentFile = "";
    m_doc->clear();
	m_imageView->clear();
    m_firstRun = true;
    updateTitle();	
}

void MainWindow::configure()
{
    if ( KConfigDialog::showDialog( "settings" ) ) {
        return; 
    }
    KConfigDialog dialog(this, "settings", CirkuitSettings::self() );
    
    QWidget* confWdg = new QWidget(&dialog);
    Ui::CirkuitGeneralForm s;
    s.setupUi(confWdg);
    s.kcfg_DefaultBackend->addItems(Cirkuit::Backend::listAvailableBackends());
    dialog.addPage( confWdg, i18n("General"), "configure" );
    
    foreach (Cirkuit::Backend* b, Cirkuit::Backend::availableBackends()) {
        dialog.addPage(b->settingsWidget(&dialog), b->config(), b->name(), b->icon() ); 
    }

    connect(&dialog, SIGNAL(settingsChanged(QString)), this, SLOT(updateConfiguration()));
    dialog.exec();
}

void MainWindow::updateConfiguration()
{
    delete m_updateTimer;

    if (CirkuitSettings::autoRefresh()) {
        m_updateTimer = new QTimer;
        m_updateTimer->setSingleShot(true);
        connect(m_updateTimer, SIGNAL(timeout()), this, SLOT(buildPreview()));
        connect(m_doc, SIGNAL(textChanged(KTextEditor::Document*)), m_updateTimer, SLOT(start()));
        m_updateTimer->setInterval(CirkuitSettings::refreshInterval()*1000);
    } else {
        m_updateTimer = 0;
    }
    
    m_backend = Cirkuit::Backend::getBackend(CirkuitSettings::defaultBackend());
}

void MainWindow::showManual()
{
    openHelpUrl(m_backend->helpUrl());
}

void MainWindow::showExamples()
{
    openHelpUrl(m_backend->examplesUrl());
}

void MainWindow::openHelpUrl(const KUrl& url)
{
    QString type;
    if (url.isLocalFile()) {
        type = KMimeType::findByUrl(url).constData()->name();
    } else {
        type = KIO::NetAccess::mimetype(url, this);
    }
    KRun::runUrl(url, type, this);
}

void MainWindow::checkCircuitMacros()
{
    cmm = new CircuitMacrosManager;
    connect(cmm, SIGNAL(newVersionAvailable(QString)), this, SLOT(askIfUpgrade(QString)));
    connect(cmm, SIGNAL(configured()), this, SLOT(circuitMacrosConfigured()));
    if (cmm->checkExistence()) {
        kDebug() << "Circuit macros found!";
        kDebug() << QString("version %1").arg(cmm->installedVersion()).toStdString().c_str();
        cmm->checkOnlineVersion();
    } else {
        kDebug() << "Circuit macros NOT found!!!!";
        if (KMessageBox::questionYesNo(this, i18n("Circuit Macros could not be found on your system. The application will not work if the macros are not installed. Do you want to proceed with the installation?"), i18n("Installation needed")) == KMessageBox::Yes) {
            cmm->downloadLatest();
            statusBar()->showMessage(i18n("Download Circuit Macros. Please wait..."));
        }
    }
}

void MainWindow::askIfUpgrade(const QString& version)
{
    if (KMessageBox::questionYesNo(this, i18n("A new version of Circuit Macros (version %1) is available. Do you want to upgrade?", version), i18n("Upgrade")) == KMessageBox::Yes) {
        cmm->downloadLatest();
    }
}

void MainWindow::circuitMacrosConfigured()
{
    statusBar()->showMessage(i18n("Ready"), 5000);
}

void MainWindow::failedNotification()
{
    m_imageView->setImage(QImage());
    statusBar()->showMessage(i18n("Unable to generate a preview for the current input"), 5000);
}

void MainWindow::showPreview(const QImage& image)
{    
    m_imageView->setImage(image, m_firstRun);
    
    m_firstRun = false;
}

void MainWindow::saveFileToDisk(const QString& path)
{
    kDebug() << "Copying "  << path << " to " << m_tempSavePath;
    QFile::copy(path, m_tempSavePath);
    statusBar()->showMessage("Export successfully completed!", 3000);
}

void MainWindow::initializeBackend()
{
    kDebug() << Cirkuit::Backend::listAvailableBackends();
    m_backend = Cirkuit::Backend::getBackend(CirkuitSettings::defaultBackend());
    
    if (!m_backend) {
        kDebug() << "The default backend has not been found";
        if (Cirkuit::Backend::listAvailableBackends().count() < 1) {
            kDebug() << "No backends available...";
            KMessageBox::error(this, i18n("No working backend has been found. Cirkuit is unable to generate any figure."), i18n("No backends found"));
        }
    }
    
    backendChanged(m_backend->name());
    m_firstRun = true;
}

void MainWindow::setDefaultBackend(const QString& backend)
{
    CirkuitSettings::setDefaultBackend(backend);
}

void MainWindow::configureKeyBindings()
{
    KShortcutsDialog::configure(actionCollection());
}

void MainWindow::configureToolbars()
{
    KParts::MainWindow::configureToolbars();
}

void MainWindow::backendChanged(const QString& backendName)
{
    actionCollection()->action("showManual")->setText(i18n("%1 manual", backendName));
    actionCollection()->action("showExamples")->setText(i18n("%1 examples", backendName));
}

void MainWindow::downloadExamples()
{
    QPointer<KNS3::DownloadDialog> dialog = new KNS3::DownloadDialog("cirkuit_example.knsrc");
    dialog->exec();
    foreach (const KNS3::Entry& e,  dialog->changedEntries())
    {
        kDebug() << "Changed Entry: " << e.name();
    }
}

void MainWindow::uploadExample()
{
    if (!m_currentFile.isLocalFile()) {
        KMessageBox::error(this, i18n("Save the current document before uploading it"));
        return;
    }
    
    KNS3::UploadDialog dialog("cirkuit_example.knsrc");
    dialog.setUploadFile(m_currentFile);
    dialog.setUploadName("A simple circuit schematic");
    dialog.exec();
}

void MainWindow::openExample()
{
    QString dir = KStandardDirs::locateLocal("appdata",  "examples");
    if (dir.isEmpty()) return;
    KStandardDirs::makeDir(dir);
    
    QPointer<KDialog> dlg=new KDialog(this);
    
    QFileSystemModel* model = new QFileSystemModel;
    model->setRootPath(dir);
    
    QListView *list = new QListView(dlg);
    list->setModel(model);
    list->setRootIndex(model->index(dir));
    list->setSelectionMode(QAbstractItemView::SingleSelection);
    dlg->setMainWidget(list);

    if (dlg->exec() == QDialog::Accepted && list->currentIndex().isValid()) {
        loadFile(model->filePath(list->currentIndex()));
    }

    delete list;
    delete dlg;
}

void MainWindow::openTemplateManager()
{
    KConfigSkeletonItem* urlItem = m_backend->configTemplateUrl();
    if (!urlItem) return;
    
    TemplateChooseDialog dlg(m_backend->id());
    
    if (dlg.exec() == QDialog::Accepted && !dlg.selectedFile().isEmpty()) {
        urlItem->setProperty(dlg.selectedFile());
        m_backend->config()->writeConfig();
    }
}

