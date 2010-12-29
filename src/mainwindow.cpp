/**************************************************************************
*   Copyright (C) 2010 by Matteo Agostinelli                              *
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
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
***************************************************************************/

#include "mainwindow.h"
#include "livepreviewwidget.h"
#include "logviewwidget.h"
#include "cirkuitsettings.h"
#include "graphicsdocument.h"
#include "circuitmacrosmanager.h"
#include "graphicsgenerator.h"
#include "settingsforms.h"

#include <KApplication>
#include <KAction>
#include <KLocale>
#include <KActionCollection>
#include <KStandardAction>
#include <KStandardDirs>
#include <KRecentFilesAction>
#include <KFileDialog>
#include <KMessageBox>
#include <KIO/NetAccess>
#include <KSaveFile>
#include <KMenu>
#include <QTextStream>
#include <QFileInfo>
#include <QTimer>
#include <KXMLGUIFactory>
#include <KConfigDialog>
#include <KStatusBar>
#include <KRun>
#include <KProcess>
#include <kmimetypetrader.h>

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

    m_doc = (GraphicsDocument*) (editor->createDocument(0));
    m_view = qobject_cast<KTextEditor::View*>(m_doc->createView(this));

    m_livePreviewWidget = new LivePreviewWidget(i18n("Live preview"), this);
    addDockWidget(Qt::TopDockWidgetArea, m_livePreviewWidget);
    
    m_logViewWidget = new LogViewWidget(i18n("Log"), this);
    addDockWidget(Qt::BottomDockWidgetArea, m_logViewWidget);
    m_logViewWidget->hide();

    mimeTypes << "application/x-cirkuit" << "text/x-tex" << "application/x-gnuplot";
    m_currentFile = KUrl("");
    updateTitle();

    setCentralWidget(m_view);
    setupActions();

    setXMLFile("cirkuitui.rc");
    createShellGUI(true);
    substituteSaveAsAction();

    guiFactory()->addClient(m_view);
    m_view->setContextMenu(qobject_cast<KMenu *> (factory()->container("ktexteditor_popup", this)));

    setGeometry(100,100,CirkuitSettings::width(),CirkuitSettings::height());

    m_generator = new GeneratorThread(GraphicsGenerator::Source, GraphicsGenerator::QtImage, m_doc);
    newCmDocument();
    
    m_updateTimer = 0;
    updateConfiguration();
    statusBar()->showMessage(i18n("Ready"), 3000);
    
    connect(m_generator, SIGNAL(finished()), this, SLOT(builtNotification()));
    connect(m_generator, SIGNAL(fail()), this, SLOT(failedNotification()));
    connect(m_doc, SIGNAL(modifiedChanged(KTextEditor::Document*)), this, SLOT(documentModified(KTextEditor::Document*)));

    connect(m_generator, SIGNAL(previewReady(QImage)), this, SLOT(showPreview(QImage)));
    connect(m_generator, SIGNAL(fileReady(QString)), this, SLOT(saveFileToDisk(QString)));
    connect(m_generator, SIGNAL(error(QString,QString)), m_logViewWidget, SLOT(displayError(QString,QString)));
    connect(m_generator, SIGNAL(output(QString,QString)), m_logViewWidget, SLOT(displayMessage(QString,QString)));
    
    checkCircuitMacros();
}

void MainWindow::setupActions()
{
    KStandardAction::quit(kapp, SLOT(quit()), actionCollection());
    KStandardAction::open(this, SLOT(openFile()), actionCollection());
    KStandardAction::save(this, SLOT(save()), actionCollection());
    KStandardAction::saveAs(this, SLOT(saveAs()), actionCollection());			
    KStandardAction::clear(this, SLOT(clear()), actionCollection());
    KStandardAction::preferences(this, SLOT(configure()),
                                            actionCollection());
                                            
    recentFilesAction = KStandardAction::openRecent(this, SLOT(loadFile( const KUrl& )),
                                                                    actionCollection());
                                                                    
    KAction* exportAction = new KAction(KIcon("document-export"), i18n("Export..."), 0);
    actionCollection()->addAction("export", exportAction);
    connect(exportAction, SIGNAL(triggered()), this, SLOT(exportFile()));

    KAction* newCmFileAction = new KAction(i18n("Circuit Macros file"), 0);
    actionCollection()->addAction("new_cmfile", newCmFileAction);
    connect(newCmFileAction, SIGNAL(triggered()), this, SLOT(newCmDocument()));

    KAction* newTikzFileAction = new KAction(i18n("TikZ file"), 0);
    actionCollection()->addAction("new_tikzfile", newTikzFileAction);
    connect(newTikzFileAction, SIGNAL(triggered()), this, SLOT(newTikzDocument()));

    KAction* newGnuplotFileAction = new KAction(i18n("Gnuplot file"), 0);
    actionCollection()->addAction("new_gnuplotfile", newGnuplotFileAction);
    connect(newGnuplotFileAction, SIGNAL(triggered()), this, SLOT(newGnuplotDocument()));

    KAction* buildPreviewAction = new KAction(i18n("Build preview"), 0);
    buildPreviewAction->setShortcut(Qt::ALT + Qt::Key_1);
    actionCollection()->addAction("build_preview", buildPreviewAction);
    connect(buildPreviewAction, SIGNAL(triggered()), this, SLOT(buildPreview()));

    KAction* openPreviewAction = new KAction(i18n("Open preview"), 0);
    openPreviewAction->setShortcut(Qt::ALT + Qt::Key_2);
    actionCollection()->addAction("open_preview", openPreviewAction);
    connect(openPreviewAction, SIGNAL(triggered()), this, SLOT(openPreview()));

    KAction* showManualAction = new KAction(KIcon("help-contents"), i18n("Show Circuit Macros manual"),0);
    actionCollection()->addAction( "showManual", showManualAction );
    connect(showManualAction, SIGNAL(triggered()), this, SLOT(showManual()));

    KAction* showExamplesAction = new KAction(i18n("Show Circuit Macros examples"),0);
    actionCollection()->addAction( "showExamples", showExamplesAction );
    connect(showExamplesAction, SIGNAL(triggered()), this, SLOT(showExamples()));

    QAction* showLivePreviewAction = m_livePreviewWidget->toggleViewAction();
    actionCollection()->addAction( "show_live_preview", showLivePreviewAction );
    
    QAction* showLogViewAction = m_logViewWidget->toggleViewAction();
    actionCollection()->addAction( "show_log_view", showLogViewAction );

    KConfig *config = CirkuitSettings::self()->config();
    recentFilesAction->loadEntries(config->group("recent_files"));
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

void MainWindow::openFile()
{
    QString filename;

    KFileDialog openFileDialog(KUrl(), "", this);
    openFileDialog.setWindowTitle(i18n("Open file - Cirkuit"));
    openFileDialog.setOperationMode(KFileDialog::Opening);
    openFileDialog.setMimeFilter(mimeTypes);
    if (openFileDialog.exec() == QDialog::Accepted) {
        filename = openFileDialog.selectedFile();
    }

    if (!filename.isEmpty()) {
        m_livePreviewWidget->clear();
        recentFilesAction->addUrl(KUrl(filename));
        loadFile(filename);
    }
}

void MainWindow::loadFile(const KUrl& url)
{
    m_currentFile = url;
    m_view->document()->openUrl(url);
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
}

void MainWindow::saveAs()
{
    QString filename;

    KFileDialog saveFileDialog(KUrl(), "", this);
    saveFileDialog.setWindowTitle(i18n("Save file - Cirkuit"));
    saveFileDialog.setOperationMode(KFileDialog::Saving);
    saveFileDialog.setMimeFilter(mimeTypes, "application/x-cirkuit");
    saveFileDialog.setConfirmOverwrite(true);
    if (saveFileDialog.exec() == QDialog::Accepted) {
        filename = saveFileDialog.selectedFile();
    }

    if (!filename.isEmpty()) {
        saveAsFile(filename);
    }
}

void MainWindow::saveAsFile(const KUrl& url)
{
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

    KFileDialog saveFileDialog(KUrl(), "", this);
    saveFileDialog.setWindowTitle(i18n("Export image - Cirkuit"));
    saveFileDialog.setStartDir(m_currentFile.directory());
    saveFileDialog.setOperationMode(KFileDialog::Saving);
    saveFileDialog.setMimeFilter(exportTypes, "application/pdf");
    saveFileDialog.setInlinePreviewShown(true);
    saveFileDialog.setConfirmOverwrite(true);
    if (saveFileDialog.exec() == QDialog::Accepted) {
        path = saveFileDialog.selectedFile();
    }

    if (!path.isEmpty()) {
        QFileInfo fileinfo(path);
        GraphicsGenerator::Format format = GraphicsGenerator::format(saveFileDialog.currentFilterMimeType()->mainExtension());
        m_generator->setup(GraphicsGenerator::Source, format, m_doc, m_currentFile.directory(), true);
        statusBar()->showMessage("Exporting image...");
        m_generator->start();
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
    CirkuitSettings::setHeight(height());
    CirkuitSettings::setWidth(width());

    KConfig *config = CirkuitSettings::self()->config();
    recentFilesAction->saveEntries(config->group("recent_files"));

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
    
    m_generator->setup(GraphicsGenerator::Source, GraphicsGenerator::QtImage, m_doc, m_currentFile.directory());
    m_generator->start();
    
    kDebug() << "Preview generation in progress...";
}

void MainWindow::openPreview()
{
    connect(m_generator, SIGNAL(finished()), this, SLOT(openPreviewFile()));
    
    buildPreview();
}

void MainWindow::openPreviewFile()
{
    KUrl url = m_generator->builder()->filePath(GraphicsGenerator::Pdf);
    KRun::runUrl(url, "application/pdf", this);
    
    disconnect(m_generator, SIGNAL(finished()), this, SLOT(openPreviewFile()));
}

void MainWindow::builtNotification()
{
    statusBar()->showMessage("Preview built", 3000);
}

void MainWindow::newDocument(GraphicsDocument::DocumentType type)
{
    if (!m_doc->closeUrl()) {
        return;
    }
    reset();

    m_doc->setType(type);
    m_doc->setText(m_doc->initialText());
    KTextEditor::Cursor cursor = m_view->cursorPosition();
    cursor.setLine(m_doc->initialCursorPosition());
    m_view->setCursorPosition(cursor);
    m_doc->setModified(false);
}

void MainWindow::newCmDocument()
{
    newDocument(GraphicsDocument::CircuitMacros);
}

void MainWindow::newTikzDocument()
{
    newDocument(GraphicsDocument::Tikz);
}

void MainWindow::newGnuplotDocument()
{
    newDocument(GraphicsDocument::Gnuplot);
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
    updateTitle();	
}

void MainWindow::configure()
{
    if ( KConfigDialog::showDialog( "settings" ) ) {
        return; 
    }
    KConfigDialog* dialog = new KConfigDialog(this, "settings", CirkuitSettings::self() );

    CirkuitGeneralForm* confWdg = new CirkuitGeneralForm();
    dialog->addPage( confWdg, i18n("General"), "configure" );
    
    CirkuitBackendForm* backendWdg = new CirkuitBackendForm();
    dialog->addPage( backendWdg, i18n("Backends"), "configure" ); 

    connect(dialog, SIGNAL(settingsChanged(QString)), this, SLOT(updateConfiguration()));
    dialog->show();
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
    
    cmm->configureIntepreter();
}

void MainWindow::showManual()
{
    KRun::runUrl(KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/doc/CMman.pdf"), "application/pdf", this);
}

void MainWindow::showExamples()
{
    KRun::runUrl(KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/examples/examples.ps"), "application/postscript", this);
}

void MainWindow::checkCircuitMacros()
{
    cmm = new CircuitMacrosManager;
    connect(cmm, SIGNAL(newVersionAvailable(const QString&)), this, SLOT(askIfUpgrade(const QString&)));
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
    KMessageBox::error(this, i18n("Unable to generate a preview for the current input"), i18n("Error"));
}

void MainWindow::showPreview(const QImage& image)
{
    m_livePreviewWidget->setImage(image);
}

void MainWindow::saveFileToDisk(const QString& path)
{
    kDebug() << "Copying "  << path << " to " << m_tempSavePath;
    QFile::copy(path, m_tempSavePath);
    statusBar()->showMessage("Export successfully completed!", 3000);
}
