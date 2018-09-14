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
#include "failcodes.h"

#include "ui_cirkuit_general_settings.h"

#include "lib/document.h"
#include "lib/backend_interface.h"
#include "lib/format.h"
#include "lib/generator.h"
#include "lib/documenttemplate.h"

#include "widgets/previewwidget.h"
#include "widgets/imageview.h"
#include "widgets/logviewwidget.h"
#include "widgets/backendchoosedialog.h"
#include "widgets/templatechoosedialog.h"

#include <QApplication>
#include <QDebug>
#include <QAction>
#include <KToggleAction>
#include <KLocalizedString>
#include <KActionCollection>
#include <KStandardAction>
#include <QStandardPaths>
#include <KRecentFilesAction>
#include <QFileDialog>
#include <KShortcutsDialog>
#include <KMessageBox>
//#include <KIO>
//#include <QSaveFile>
#include <QMenu>
#include <QTextStream>
#include <QListWidget>
#include <QFileInfo>
#include <QFileSystemModel>
#include <QTimer>
#include <QMimeType>
#include <QMimeDatabase>
#include <KXMLGUIFactory>
#include <KConfigDialog>
#include <KRun>
#include <KProcess>
#include <KConfigSkeleton>
#include <KMessageWidget>
#include <KTextEditor/Document>
#include <KTextEditor/Editor>
#include <KTextEditor/View>
//#include <KNS3/DownloadDialog>
//#include <KNS3/UploadDialog>

#include "widgets/widgetfloater.h"

//#include <kmimetypetrader.h>

MainWindow::MainWindow(QWidget *)
{
    KTextEditor::Editor *editor = KTextEditor::Editor::instance();

    if (!editor) {
        KMessageBox::error(this, i18n("A KF5 text-editor component could not be found;\n"
        "please check your KF5 installation."));
        qApp->exit(1);
    }

    m_doc = (Cirkuit::Document*) (editor->createDocument(0));
    m_doc->initialize();
    m_view = qobject_cast<KTextEditor::View*>(m_doc->createView(this));
   
    m_previewWidget = new PreviewWidget(i18n("Preview"), this);
    m_previewWidget->setObjectName("preview-dock");
    m_imageView = m_previewWidget->view();
    addDockWidget(Qt::TopDockWidgetArea, m_previewWidget);

    m_messageWidget = 0;

    m_logViewWidget = new LogViewWidget(i18n("Log"), this);
    m_logViewWidget->setObjectName("log-dock");
    addDockWidget(Qt::BottomDockWidgetArea, m_logViewWidget);
    m_logViewWidget->hide();

    m_currentFile = QString();
    m_dirCurrentEditorFile = QDir::current().absolutePath();
    updateTitle();

    setCentralWidget(m_view);
    setAutoSaveSettings();
    setupActions();

    setXMLFile("cirkuitui.rc");
    createShellGUI(true);

    guiFactory()->addClient(m_view);
    m_view->setContextMenu(qobject_cast<QMenu *> (factory()->container("ktexteditor_popup", this)));

    m_generator = new GeneratorThread;
    
    m_updateTimer = 0;
    updateConfiguration();
    
    connect(m_generator, SIGNAL(success()), this, SLOT(builtNotification()));
    connect(m_generator, SIGNAL(fail(const int)), this, SLOT(failedNotification(const int)));
    connect(m_doc, SIGNAL(modifiedChanged(KTextEditor::Document*)), this, SLOT(documentModified(KTextEditor::Document*)));

    connect(m_generator, SIGNAL(previewReady(QImage)), this, SLOT(showPreview(QImage)));
    connect(m_generator, SIGNAL(fileReady(QString)), this, SLOT(saveFileToDisk(QString)));
    connect(m_generator, SIGNAL(error(QString,QString)), m_logViewWidget, SLOT(displayError(QString,QString)));
    connect(m_generator, SIGNAL(output(QString,QString)), m_logViewWidget, SLOT(displayMessage(QString,QString)));   
    connect(m_generator, SIGNAL(previewUrl(QString)), m_imageView, SLOT(setPdfUrl(QString)));
    connect(m_generator, SIGNAL(backendChanged(QString)), this, SLOT(backendChanged(QString)));
    
    checkCircuitMacros();

    qDebug() << "Initializing backends";
    initializeBackend();
    newDocument();
}

void MainWindow::setupActions()
{
    // re-connect save and save as
    QAction* action = m_view->actionCollection()->action(KStandardAction::name(KStandardAction::Save));
    action->disconnect(SIGNAL(triggered(bool)));
    connect(action, SIGNAL(triggered()), this, SLOT(save()));
    action = m_view->actionCollection()->action(KStandardAction::name(KStandardAction::SaveAs));
    action->disconnect(SIGNAL(triggered(bool)));
    connect(action, SIGNAL(triggered()), this, SLOT(saveAs()));
    
    KStandardAction::openNew(this, SLOT(newFile()), actionCollection());
    KStandardAction::quit(this, SLOT(close()), actionCollection());
    KStandardAction::open(this, SLOT(openFile()), actionCollection());
    KStandardAction::close(this, SLOT(newDocument()), actionCollection());
    KStandardAction::clear(this, SLOT(clear()), actionCollection());
    KStandardAction::preferences(this, SLOT(configure()), actionCollection());

    KStandardAction::keyBindings(this, SLOT(configureKeyBindings()), actionCollection());
    KStandardAction::configureToolbars(this, SLOT(configureToolbars()), actionCollection());
                                            
    recentFilesAction = KStandardAction::openRecent(this, SLOT(loadFileFromUrl(QUrl)),
                                                                    actionCollection());
                                                                    
    QAction* exportAction = new QAction(QIcon("document-export"), i18n("Export image..."), 0);
    actionCollection()->addAction("export", exportAction);
    connect(exportAction, SIGNAL(triggered()), this, SLOT(exportFile()));

    QAction* buildPreviewAction = new QAction(i18n("Build preview"), 0);
    actionCollection()->setDefaultShortcut(buildPreviewAction, Qt::ALT + Qt::Key_1);
    buildPreviewAction->setIcon(QIcon("run-build"));
    actionCollection()->addAction("build_preview", buildPreviewAction);
    connect(buildPreviewAction, SIGNAL(triggered()), this, SLOT(buildPreview()));

    QAction* openPreviewAction = new QAction(i18n("Open preview"), 0);
    actionCollection()->setDefaultShortcut(openPreviewAction, Qt::ALT + Qt::Key_2);
    openPreviewAction->setIcon(QIcon("document-preview"));
    actionCollection()->addAction("open_preview", openPreviewAction);
    connect(openPreviewAction, SIGNAL(triggered()), this, SLOT(openPreview()));
    
    QAction* templateManagerAction = new QAction(i18n("Template manager"), 0);
    actionCollection()->addAction("template_manager", templateManagerAction);
    connect(templateManagerAction, SIGNAL(triggered()), this, SLOT(openTemplateManager()));

    QAction* showManualAction = new QAction(QIcon("help-contents"), i18n("Show manual"),0);
    actionCollection()->addAction( "showManual", showManualAction );
    connect(showManualAction, SIGNAL(triggered()), this, SLOT(showManual()));

    QAction* showExamplesAction = new QAction(i18n("Show examples"),0);
    actionCollection()->addAction( "showExamples", showExamplesAction );
    connect(showExamplesAction, SIGNAL(triggered()), this, SLOT(showExamples()));

    QAction* showLivePreviewAction = m_previewWidget->toggleViewAction();
    showLivePreviewAction->setIcon(QIcon("document-preview"));
    actionCollection()->addAction( "show_live_preview", showLivePreviewAction );

 /*   QAction* downloadExamples = new QAction(i18n("Download Examples"), actionCollection());
    downloadExamples->setIcon(QIcon("get-hot-new-stuff"));
    actionCollection()->addAction("download_examples",  downloadExamples);
    connect(downloadExamples, SIGNAL(triggered()), this,  SLOT(downloadExamples()));
    
    QAction* uploadExample = new QAction(i18n("Upload Example"), actionCollection());
    uploadExample->setIcon(QIcon("get-hot-new-stuff"));
    actionCollection()->addAction("upload_example",  uploadExample);
    connect(uploadExample, SIGNAL(triggered()), this,  SLOT(uploadExample()));
    
    QAction* openExample =new QAction(i18n("&Open Example"), actionCollection());
    openExample->setIcon(QIcon("document-open"));
    actionCollection()->addAction("file_open_example", openExample);
    connect(openExample, SIGNAL(triggered()), this, SLOT(openExample()));    
*/    
    QAction* showLogViewAction = m_logViewWidget->toggleViewAction();
    actionCollection()->addAction( "show_log_view", showLogViewAction );
    showLogViewAction->setIcon(QIcon("documentation"));

    KConfig *config = CirkuitSettings::self()->config();
    recentFilesAction->loadEntries(config->group("recent_files"));

    m_imageView->setupActions(actionCollection());
    m_imageView->zoomFitPageAction()->setChecked(CirkuitSettings::zoomToFit());
    m_imageView->updateZoomToFit();
}

void MainWindow::clear()
{
    m_doc->clear();
}

void MainWindow::newFile()
{
    BackendChooseDialog *dialog = new BackendChooseDialog(CirkuitSettings::defaultBackend(), this);
  //  QPointer<BackendChooseDialog> dlg = new BackendChooseDialog(CirkuitSettings::defaultBackend(), this);
    
    connect(dialog, SIGNAL(backendSelected(QString)), this, SLOT(newDocument(QString)));
    connect(dialog, SIGNAL(defaultBackendSelected(QString)), this, SLOT(setDefaultBackend(QString)));
    
    dialog->exec();
    delete dialog;
}

void MainWindow::openFile()
{
    QString openFileName = QFileDialog::getOpenFileName(this, i18n("Open file - Cirkuit"),  m_dirCurrentEditorFile,
                                                        i18n("Cirkuit drawing (*.m4 *.ckt);;Tex (*.tex);;Gnuplot (*.gp);;All files (*.*)") );
    if (!openFileName.isEmpty()) {
        m_imageView->clear();
        recentFilesAction->addUrl(QUrl(openFileName));
        loadFile(openFileName);
    }
}

void MainWindow::loadFile(const QString& fnpath)
{
    QUrl url = QUrl::fromLocalFile(fnpath);
    loadFileFromUrl2(url, fnpath);
}

void MainWindow::loadFileFromUrl(const QUrl& url)
{
    loadFileFromUrl2(url, url.toLocalFile() );
}

void MainWindow::loadFileFromUrl2(const QUrl& url, const QString& fnpath)
{
    bool ok = m_view->document()->openUrl(url);
    if (!ok) return;
    m_currentFile = fnpath;
    QFileInfo fi(m_currentFile);
    m_dirCurrentEditorFile = fi.dir().absolutePath();
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
    QString saveFileName = QFileDialog::getSaveFileName(this, i18n("Save file - Cirkuit"),     m_dirCurrentEditorFile,
                                                          i18n("Cirkuit drawing (*.m4, *.ckt);;Tex (*.tex);;Gnuplot (*.gp);;All files (*.*)") );

    if (!saveFileName.isEmpty()) {
        saveAsFile(saveFileName);
    }
}

void MainWindow::saveAsFile(const QString& fnpath)
{
    if (CirkuitSettings::refreshOnSave()) {
        buildPreview();
    }
    QUrl url = QUrl::fromLocalFile(fnpath);
    m_doc->saveAs(QUrl(url));
    recentFilesAction->addUrl(url);
    m_currentFile = fnpath;
    QFileInfo fi(m_currentFile);
    m_dirCurrentEditorFile = fi.dir().absolutePath();
    updateTitle();
}

void MainWindow::exportFile()
{

    QStringList exportTypes;

    QString saveFileName = QFileDialog::getSaveFileName(this, i18n("Export image - Cirkuit"), m_dirCurrentEditorFile,
                                      i18n("pdf (*.pdf);;png(*.png);;jpg(*.jpg);;eps(*.eps);;svg(*.svg);;gif(*.gif);;Document(*.tex)") );

    if (!saveFileName.isEmpty()) {
        QFileInfo fileinfo(saveFileName);
        QString sfx = fileinfo.suffix().toLower(); // e.g. "pdf", "png" (dot-less)
        Cirkuit::Format format = Cirkuit::Format::fromExtension(sfx);
        m_tempSavePath = saveFileName;
        m_generator->generate(Cirkuit::Format::Source, format, m_backend, m_doc, true);
        // saveFileToDisk() called after fileReady event emitted in generatorThread.
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
    delete m_messageWidget;
    QString msg = i18n("Generating preview");

    m_messageWidget = new KMessageWidget;
    m_messageWidget->setMessageType(KMessageWidget::Information);
    m_messageWidget->setText(msg);
    showMessage(m_messageWidget);
    m_logViewWidget->clear();
    m_logViewWidget->hide();
    m_generator->generate(Cirkuit::Format::Source, Cirkuit::Format::QtImage, m_backend, m_doc, false, m_imageView->scaleFactor());
}

void MainWindow::openPreview()
{
    connect(m_generator, SIGNAL(finished()), this, SLOT(openPreviewFile()));
    
    buildPreview();
}

void MainWindow::openPreviewFile()
{
    disconnect(m_generator, SIGNAL(finished()), this, SLOT(openPreviewFile()));
    
    QUrl url = QUrl(m_generator->previewUrl());
    if (!url.isLocalFile()) {    
        return;
    }
    
    KRun::runUrl(url, "application/pdf", this);
}

void MainWindow::builtNotification()
{
    m_messageWidget->animatedHide();
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
    mainreset();
    
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
        QFileInfo fi(m_currentFile);
        m_windowTitle += " - " + fi.fileName();
    }
    
    m_windowTitle += "[*]";
    setWindowTitle(m_windowTitle);
}

void MainWindow::mainreset()
{
    m_currentFile = QString();
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

void MainWindow::openHelpUrl(const QString& fnpath)
{

        QMimeDatabase db;
        QString fn = QFileInfo(fnpath).fileName();
        QString mimtype;
        QUrl url(fnpath);
      if (url.isLocalFile()) {
           mimtype = db.mimeTypeForFile(fn).name();
      } else {
          mimtype = db.mimeTypeForFile(fn).name();  // for now.  QNetworkAccessManager might be better for web locations
//        mimtype = KIO::NetAccess::mimetype(url, this); // old
      }
    KRun::runUrl(url, mimtype, this, KRun::RunFlags());
}

void MainWindow::checkCircuitMacros()
{
    cmm = new CircuitMacrosManager;
    connect(cmm, SIGNAL(newVersionAvailable(QString)), this, SLOT(askIfUpgrade(QString)));
    connect(cmm, SIGNAL(configured()), this, SLOT(circuitMacrosConfigured()));
    if (cmm->checkExistence()) {
        qDebug() << "Circuit macros found!";
        qDebug() << QString("version %1").arg(cmm->installedVersion());
        cmm->checkOnlineVersion();
    } else {
        qDebug() << "Circuit macros NOT found!!!!";
        if (KMessageBox::questionYesNo(this, i18n("Circuit Macros could not be found on your system. The application will not work if the macros are not installed. Do you want to proceed with the installation?"), i18n("Installation needed")) == KMessageBox::Yes) {
            cmm->downloadLatest();

            delete m_messageWidget;
            m_messageWidget = new KMessageWidget(m_imageView);
            m_messageWidget->setMessageType(KMessageWidget::Information);
            m_messageWidget->setText(i18n("Downloading Circuit Macros. Please wait..."));
            showMessage(m_messageWidget);

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

    if (m_messageWidget) {
        m_messageWidget->animatedHide();
    }
}

void MainWindow::failedNotification(const int fcode)
{
    QString msg = i18n(GetErrorString(fcode)) +
                  i18n("\nUnable to generate a preview for the current input");

    m_imageView->setImage(QImage());
    delete m_messageWidget;
    m_messageWidget = new KMessageWidget(m_imageView);
    m_messageWidget->setMessageType(KMessageWidget::Error);
    m_messageWidget->setText(msg);
    showMessage(m_messageWidget);

    delete m_messageWidget;
    m_messageWidget = new KMessageWidget(m_imageView);
    m_messageWidget->setMessageType(KMessageWidget::Error);
    m_messageWidget->setText(msg);
    showMessage(m_messageWidget);
}

void MainWindow::showPreview(const QImage& image)
{    
    m_imageView->setImage(image, m_firstRun);
    
    m_firstRun = false;
}

void MainWindow::saveFileToDisk(const QString& path)
{
    qDebug() << "Copying "  << path << " to " << m_tempSavePath;
    // QFile::copy does not overwrite, so delete old copy before saving.
    if (QFile::exists(m_tempSavePath)) QFile::remove(m_tempSavePath);
    QFile::copy(path, m_tempSavePath);
    qDebug() << "File successfully exported";
}

void MainWindow::initializeBackend()
{
    qDebug() << Cirkuit::Backend::listAvailableBackends();
    m_backend = Cirkuit::Backend::getBackend(CirkuitSettings::defaultBackend());
    
    if (!m_backend) {
        qDebug() << "The default backend has not been found";
        if (Cirkuit::Backend::listAvailableBackends().count() < 1) {
            qDebug() << "No backends available...";
            KMessageBox::error(this, i18n("No working backend has been found. Cirkuit is unable to generate any figure."), i18n("No backends found"));
            return;
        } else {
            // try falling back to the first available backend
            m_backend = Cirkuit::Backend::getBackend(Cirkuit::Backend::listAvailableBackends().at(0));
            if (!m_backend) {
                // this shouldn't happen
                return;
            }
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

/*
void MainWindow::downloadExamples()
{
    KNS3::DownloadDialog* dialog = new KNS3::DownloadDialog("cirkuit_example.knsrc", this);
    dialog->exec();
    foreach (const KNS3::Entry& e,  dialog->changedEntries())
    {
        qDebug() << "Changed Entry: " << e.name();
    }
    delete dialog;
}

void MainWindow::uploadExample()
{
    qDebug() << "Uploading to GHNS: " << m_currentFile;
    
    if (!m_currentFile.isLocalFile()) {
        qDebug() << "Trying to save the file first ...";
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
    QString dir = QStandardPaths::locate(QStandardPaths::AppLocalDataLocation, "examples");
    if (dir.isEmpty()) return;
    QDir dirpath;
    dirpath.mkpath(dir);
    
  //  QPointer<QDialog> dlg=new QDialog(this);
    QDialog *dlg = new QDialog;
    
    QFileSystemModel* model = new QFileSystemModel;
    model->setRootPath(dir);
    
    QListView *view = new QListView(dlg);
    view->setModel(model);
    view->setRootIndex(model->index(dir));
    view->setSelectionMode(QAbstractItemView::SingleSelection);

//    dlg->setMainWidget(view);
    dlg->listView->setModel(model);
    if (dlg->exec() == QDialog::Accepted && view->currentIndex().isValid()) {
        loadFile( QUrl(model->filePath(view->currentIndex())) );
    }

    delete view;
    delete dlg;
}
*/

void MainWindow::openTemplateManager()
{
    KConfigSkeletonItem* urlItem = m_backend->configTemplateUrl();
    if (!urlItem) return;

    TemplateChooseDialog dlg(m_backend->id(), urlItem->property().toUrl() );
    
    if (dlg.exec() == QDialog::Accepted && !dlg.selectedFile().isEmpty()) {
        QUrl sel_url = dlg.selectedFile();
        urlItem->setProperty(sel_url);
        m_backend->config()->writeConfig();

        delete m_messageWidget;
        QString msg = i18n("Generating preview");

        m_messageWidget = new KMessageWidget;
        m_messageWidget->setMessageType(KMessageWidget::Information);
        m_messageWidget->setText(msg);
        showMessage(m_messageWidget);
        m_logViewWidget->clear();
        m_logViewWidget->hide();
        m_generator->generate(Cirkuit::Format::Source, Cirkuit::Format::QtImage, m_backend, m_doc, false, m_imageView->scaleFactor());
    }
}

void MainWindow::showMessage(KMessageWidget* messageWidget)
{
    WidgetFloater* floater = new WidgetFloater(m_imageView);
    floater->setChildWidget(messageWidget);
    floater->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    messageWidget->animatedShow();
}

