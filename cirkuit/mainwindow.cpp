#include "mainwindow.h"
#include "kcircuitmacrossettings.h"
#include "kcmgeneralsettings.h"
#include "circuitbuilder.h"
#include "livepreviewwidget.h"
#include "twotermdialog.h"
#include "circuitmacrosmanager.h"
#include "externalbinmanager.h"

#include <krecentfilesaction.h>
#include <KLocalizedString>
#include <KApplication>
#include <KAction>
#include <KLocale>
#include <KActionCollection>
#include <KStandardAction>
#include <KStandardDirs>
#include <KFileDialog>
#include <KUrl>
#include <KStatusBar>
#include <KMessageBox>
#include <KNotification>
#include <KMenuBar>
#include <KConfigDialog>
#include <kio/netaccess.h>
#include <QDockWidget>
#include <QTimer>
#include <QCloseEvent>
#include <QDesktopServices>
#include <QProcess>
#include <QDebug>
 
MainWindow::MainWindow(QWidget *parent)
    : KXmlGuiWindow(parent)
{
  textArea = new KTextEdit;
  setCentralWidget(textArea);
  
  lineNumberLabel = new QLabel;
  statusBar()->addPermanentWidget(lineNumberLabel);
  
  builder = new CircuitBuilder;
  connect(builder, SIGNAL(previewBuilt(const QImage&)), this, SLOT(updatePreview(const QImage&)));
  mimeTypes << "application/x-cirkuit";
  
  QFont font("Monospace", 10);
  textArea->setFont(font);
  textArea->setText(".PS\ncct_init\n\n\n.PE");
  textArea->moveCursor(QTextCursor::Down);
  textArea->moveCursor(QTextCursor::Down);
  textArea->moveCursor(QTextCursor::Down);
  setCurrentLineNumber();

  tempFileName = KStandardDirs::locateLocal("data", "cirkuit/build/temp", true);

  updateTimer = new QTimer;
  updateTimer->setSingleShot(true);
  updateConfiguration();

  connect(textArea->document(), SIGNAL(contentsChanged()),
           updateTimer, SLOT(start()));
			  
	connect(textArea, SIGNAL(cursorPositionChanged()), this, SLOT(setCurrentLineNumber())),
           
  connect(updateTimer, SIGNAL(timeout()),
                    this, SLOT(build()));
                      
  createLivePreviewWidget();
  setupActions();  
  checkCircuitMacros();
  setCurrentFile("");

  ExternalBinManager manager;
  if (!manager.checkAll())
  {
	  if (KMessageBox::warningContinueCancel(0, i18n("Some required applications cannot be found on your path.<p>Cirkuit will not work properly unless these applications are installed: <b>%1</b>.<p>Do you want to continue anyway?").arg(manager.missingApps().join(", ")), i18n("Warning")) != KMessageBox::Continue)
	  {
		  close();
	  }
  }
}

MainWindow::~MainWindow()
{
	
}
 
void MainWindow::setupActions()
{
  connect(textArea, SIGNAL(textChanged()), this, SLOT(updateModifiedStatus()));
 
  QAction* showDockAction = liveWidget->toggleViewAction();
  actionCollection()->addAction( "showDock", showDockAction );
  
  KStandardAction::quit(this, SLOT(close()),
                        actionCollection());

  KStandardAction::openNew(this, SLOT(clearSlot()),
                        actionCollection());
  
  KStandardAction::open(this, SLOT(openSlot()),
			actionCollection());
      
  recentFilesAction = KStandardAction::openRecent(this, SLOT(openSlot( const KUrl& )),
                             actionCollection());

  KStandardAction::close(this, SLOT(clearSlot()),
                           actionCollection());

  KStandardAction::save(this, SLOT(saveSlot()),
                        actionCollection());

  KStandardAction::saveAs(this, SLOT(saveAsSlot()),
                        actionCollection());
                        
  KStandardAction::preferences(this, SLOT(configureSlot()),
                               actionCollection());
                               
  KStandardAction::undo(textArea, SLOT(undo()), actionCollection());
  KStandardAction::redo(textArea, SLOT(redo()), actionCollection());                                 
  KStandardAction::copy(textArea, SLOT(copy()), actionCollection());
  KStandardAction::cut(textArea, SLOT(cut()), actionCollection());
  KStandardAction::paste(textArea, SLOT(paste()), actionCollection());
  KStandardAction::selectAll(textArea, SLOT(selectAll()), actionCollection());
                               
  KAction* showManualAction = new KAction(KIcon("book"), i18n("Show Circuit Macros manual"),0);
  actionCollection()->addAction( "showManual", showManualAction );
  connect(showManualAction, SIGNAL(triggered()), this, SLOT(showManual()));
  
  KAction* showExamplesAction = new KAction(i18n("Show Circuit Macros examples"),0);
  actionCollection()->addAction( "showExamples", showExamplesAction );
  connect(showExamplesAction, SIGNAL(triggered()), this, SLOT(showExamples()));
  
  KAction* previewEpsAction = new KAction(i18n("Preview EPS..."), 0);
  previewEpsAction->setShortcut(Qt::CTRL + Qt::Key_0);
  actionCollection()->addAction("previewEps", previewEpsAction);
  connect(previewEpsAction, SIGNAL(triggered()), this, SLOT(previewEps()));
  
  KAction* refreshPreviewAction = new KAction(i18n("Refresh preview"), 0);
  refreshPreviewAction->setShortcut(Qt::CTRL + Qt::Key_P);
  actionCollection()->addAction("refreshPreview", refreshPreviewAction);
  connect(refreshPreviewAction, SIGNAL(triggered()), this, SLOT(build()));
  
  KAction* exportToEpsAction = new KAction(i18n("Export to EPS..."), 0);
  exportToEpsAction->setShortcut(Qt::CTRL + Qt::Key_1);
  actionCollection()->addAction("exportToEps", exportToEpsAction);
  connect(exportToEpsAction, SIGNAL(triggered()), this, SLOT(exportToEps()));

  KAction* exportToPdfAction = new KAction(i18n("Export to PDF..."), 0);
  exportToPdfAction->setShortcut(Qt::CTRL + Qt::Key_2);
  actionCollection()->addAction("exportToPdf", exportToPdfAction);
  connect(exportToPdfAction, SIGNAL(triggered()), this, SLOT(exportToPdf()));
  
  KAction* exportToPngAction = new KAction(i18n("Export to PNG..."), 0);
  exportToPngAction->setShortcut(Qt::CTRL + Qt::Key_3);
  actionCollection()->addAction("exportToPng", exportToPngAction);
  connect(exportToPngAction, SIGNAL(triggered()), this, SLOT(exportToPng()));
  
  KAction* exportToPstAction = new KAction(i18n("Export to PSTricks..."), 0);
  exportToPstAction->setShortcut(Qt::CTRL + Qt::Key_4);
  actionCollection()->addAction("exportToPst", exportToPstAction);
  connect(exportToPstAction, SIGNAL(triggered()), this, SLOT(exportToPst()));
  
  KAction* exportToPsAction = new KAction(i18n("Export to PostScript..."), 0);
  exportToPsAction->setShortcut(Qt::CTRL + Qt::Key_5);
  actionCollection()->addAction("exportToPs", exportToPsAction);
  connect(exportToPsAction, SIGNAL(triggered()), this, SLOT(exportToPs()));
  
  KAction* exportToSvgAction = new KAction(i18n("Export to SVG..."), 0);
  exportToSvgAction->setShortcut(Qt::CTRL + Qt::Key_6);
  actionCollection()->addAction("exportToSvg", exportToSvgAction);
  connect(exportToSvgAction, SIGNAL(triggered()), this, SLOT(exportToSvg()));
  
  KAction* insertTwoTermAction = new KAction(i18n("Two-Terminal Element..."),0);
  insertTwoTermAction->setShortcut(Qt::CTRL + Qt::Key_T);
  actionCollection()->addAction("insertTwoTerm", insertTwoTermAction);
  connect(insertTwoTermAction, SIGNAL(triggered()), this, SLOT(showTwoTermDialog()));

  KConfig *config = KCircuitMacrosSettings::self()->config();
  recentFilesAction->loadEntries(config->group("RecentFiles"));
  setupGUI();
}

void MainWindow::createLivePreviewWidget()
{
  liveWidget = new LivePreviewWidget(i18n("Live preview"), this);
 
  addDockWidget(Qt::TopDockWidgetArea, liveWidget);
}

void MainWindow::openSlot(const KUrl& url)
{
  if (askIfModified())
  {
    QString path;
    if (url.url().isEmpty())
	{
		KFileDialog openFileDialog(KUrl(), "", this);
		openFileDialog.setOperationMode(KFileDialog::Opening);
		openFileDialog.setMimeFilter(mimeTypes);
		if (openFileDialog.exec() == QDialog::Accepted)
			path = openFileDialog.selectedFile();
	}
    else
      path = url.url();
    
    if (!path.isEmpty())
    {
      liveWidget->clear();
      recentFilesAction->addUrl(KUrl(path));
      fileName = path;    
      loadFile(fileName);
    }
  }
}

bool MainWindow::loadFile(const KUrl& fileName)
{
    if (fileName.isEmpty()) return false;
  
    if (!KIO::NetAccess::exists(fileName, true, this))
    {
      KMessageBox::error (this, i18n("The given file could not be read, check if it exists or if it is readable for the current user."));
      return false;
    }
  
    QFile file(fileName.path());
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
      QMessageBox::warning(this, i18n("Cirkuit"),
                         i18n("Cannot read file %1:\n%2.", fileName.fileName(), file.errorString()));
      return false;
    }

    QTextStream in(&file);
    KApplication::setOverrideCursor(Qt::WaitCursor);
    textArea->setPlainText(in.readAll());
    KApplication::restoreOverrideCursor();

    setCurrentFile(fileName.path());
    statusBar()->showMessage(i18n("File loaded"), 2000);
    build();
    return true;
}

void MainWindow::clearSlot()
{
  if (askIfModified())
  {
    textArea->clear();
	 textArea->document()->setPlainText(".PS\ncct_init\n\n.PE");
    textArea->moveCursor(QTextCursor::Down);
    textArea->moveCursor(QTextCursor::Down);
    liveWidget->clear();
    setCurrentFile("");
  }
}

bool MainWindow::saveSlot()
{
  if (isUntitled())
  {
    return saveAsSlot();
  }
  else
  {
	  return saveFile(fileName);
  }
}

bool MainWindow::saveAsSlot()
{
	QString path = "";
	KFileDialog saveFileDialog(KUrl(), "", this);
	saveFileDialog.setOperationMode(KFileDialog::Saving);
	saveFileDialog.setMimeFilter(mimeTypes);
	if (saveFileDialog.exec() == QDialog::Accepted)
		path = saveFileDialog.selectedFile();

	if (path.isEmpty())
		return false;

  if (QFile::exists(path) && KMessageBox::questionYesNoCancel(this, i18n("File already exists. Do you want to overwrite?"), i18n("Overwrite")) != KMessageBox::Yes)
	return false;

  if (!path.isEmpty())
    return saveFile(path);
  
  return false;
}

bool MainWindow::saveFile(const QString& fileName, bool temporary)
{
  QFile file(fileName);
  if (!file.open(QFile::WriteOnly | QFile::Text)) {
	QMessageBox::warning(this, i18n("Cirkuit"),
                          i18n("Cannot write file %1:\n%2."),fileName,file.errorString());
    return false;
  }
  
  QTextStream out(&file);
  KApplication::setOverrideCursor(Qt::WaitCursor);
  out << textArea->toPlainText();
  KApplication::restoreOverrideCursor();
  
  if (!temporary)
  {
    setCurrentFile(fileName);
    statusBar()->showMessage(i18n("File saved"), 2000);
  }
  
  return true;
}

bool MainWindow::askIfModified()
{
  if (textArea->document()->isModified())
  {
    switch (KMessageBox::questionYesNoCancel(this, i18n("The document has been modified. Do you want to save changes?"), i18n("Close document")))
    {
      case KMessageBox::Yes :
        return saveSlot();
      case KMessageBox::No :
        return true;
      case KMessageBox::Cancel :
        return false;
    }
  }
  
  return true;
}

void MainWindow::updateModifiedStatus(bool b)
{
  setWindowModified(b);
}

bool MainWindow::isUntitled() const
{
  return fileName.isEmpty();
}

void MainWindow::setCurrentFile(const QString& filename)
{
  if (filename.isEmpty()) 
  {
    fileName = "";
    setWindowTitle(i18n("%1[*] - %2", i18n("Untitled"), i18n("Cirkuit")));
  } 
  else 
  {
    fileName = QFileInfo(filename).canonicalFilePath();
    setWindowTitle(i18n("%1[*] - %2", QFileInfo(fileName).fileName(), i18n("Cirkuit")));
  }

  textArea->document()->setModified(false);
  updateModifiedStatus(false);
}

void MainWindow::configureSlot()
{
  if ( KConfigDialog::showDialog( "settings" ) )
    return; 
  
  KConfigDialog* dialog = new KConfigDialog(this, "settings", KCircuitMacrosSettings::self());
  KCMGeneralSettings* confWdg = new KCMGeneralSettings; 
  dialog->addPage( confWdg, i18n("General"), "configure" ); 
  
  connect( dialog, SIGNAL(settingsChanged(const QString&)), this, SLOT(updateConfiguration()) ); 
           
  dialog->show();
}

void MainWindow::updateConfiguration()
{
  updateTimer->setInterval(KCircuitMacrosSettings::refreshInterval());
}

void MainWindow::build()
{
  if (!saveFile(tempFileName + ".cir", true))
    return;
  
  statusBar()->showMessage(i18n("Building circuit..."));
  builder->build(KUrl(tempFileName), QFileInfo(fileName).absolutePath());
}

void MainWindow::closeEvent ( QCloseEvent *event)   
{
  if (!askIfModified())
  {
    event->ignore();
    return;
  }
  
  KConfig *config = KCircuitMacrosSettings::self()->config();
  recentFilesAction->saveEntries(config->group("RecentFiles"));
  event->accept();
}

void MainWindow::updatePreview(const QImage& image)
{
	statusBar()->showMessage(i18n("Circuit built"), 2000);
	
	updateTimer->stop();
	KNotification *notify = 0;
	notify = new KNotification("Preview Generated");
	notify->setComponentData(KComponentData("cirkuit"));
	notify->setText(i18n("The preview has been generated"));
	notify->sendEvent();
    
  liveWidget->setImage(image);
}

void MainWindow::showManual()
{
  QProcess* previewProc = new QProcess;
  
  QStringList args;
  args << KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/doc/CMman.pdf");
  
  previewProc->start("okular", args);  
}

void MainWindow::showExamples()
{
  QProcess* previewProc = new QProcess;
  
  QStringList args;
  args << KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/examples/examples.ps");
  
  previewProc->start("okular", args);  
}

void MainWindow::exportToEps()
{
  build();
  
  QString path = KFileDialog::getSaveFileName(KUrl(), "*.eps|" + i18n("EPS files (*.eps)"));
  
  if (path != 0)
  {
    if (QFile::exists(path))
      QFile::remove(path);
    
    QFile::copy(builder->epsFilePath(), path);
  }
}

void MainWindow::exportToPdf()
{
  build();
  
  QString path = KFileDialog::getSaveFileName(KUrl(), "*.pdf|" + i18n("PDF files (*.pdf)"));
  
  if (path != 0)
  {
    if (QFile::exists(path))
      QFile::remove(path);
    
    QFile::copy(builder->pdfFilePath(), path);
  }
}

void MainWindow::exportToPng()
{
  build();
  
  QString path = KFileDialog::getSaveFileName(KUrl(), "*.png|" + i18n("PNG files (*.png)"));
  
  if (path != 0)
  {
    if (QFile::exists(path))
      QFile::remove(path);
    
    QFile::copy(builder->pngFilePath(), path);
  }
}

void MainWindow::exportToPst()
{
  build();
  
  QString path = KFileDialog::getSaveFileName(KUrl(), "*.tex|" + i18n("PSTricks files (*.tex)"));
  
  if (path != 0)
  {
    if (QFile::exists(path))
      QFile::remove(path);
    
    QFile::copy(builder->pstFilePath(), path);
  }
}

void MainWindow::exportToPs()
{
	build();
	
	QString path = KFileDialog::getSaveFileName(KUrl(), "*.ps|" + i18n("PostScript files (*.ps)"));
	
	if (path != 0)
	{
		if (QFile::exists(path))
			QFile::remove(path);
		
		QFile::copy(builder->psFilePath(), path);
	}
}

void MainWindow::exportToSvg()
{
	build();
	
	QString path = KFileDialog::getSaveFileName(KUrl(), "*.svg|" + i18n("SVG files (*.svg)"));
	
	if (path != 0)
	{
		if (QFile::exists(path))
			QFile::remove(path);
		
		QFile::copy(builder->svgFilePath(), path);
	}
}

void MainWindow::previewEps()
{
  QProcess* previewProc = new QProcess;
  
  QStringList args;
  args << builder->epsFilePath();
  
  previewProc->start("okular", args);  
}

void MainWindow::showTwoTermDialog()
{
  TwoTermDialog dlg;
  dlg.exec();
}

void MainWindow::checkCircuitMacros()
{
	cmm = new CircuitMacrosManager;
	connect(cmm, SIGNAL(newVersionAvailable(const QString&)), this, SLOT(askIfUpgrade(const QString&)));
	connect(cmm, SIGNAL(configured()), this, SLOT(circuitMacrosConfigured()));
	if (cmm->checkExistence())
	{
		qDebug() << "Circuit macros found!";
		qDebug() << QString("version %1").arg(cmm->installedVersion()).toStdString().c_str();
		cmm->checkOnlineVersion();
	}

	else
	{
		qDebug() << "Circuit macros NOT found!!!!";
		if (KMessageBox::questionYesNo(this, i18n("Circuit Macros could not be found on your system. The application will not work if the macros are not installed. Do you want to proceed with the installation?"), i18n("Installation needed")) == KMessageBox::Yes)
		{
			cmm->downloadLatest();
			statusBar()->showMessage(i18n("Download Circuit Macros. Please wait..."));
		}
	}
}

void MainWindow::askIfUpgrade(const QString& version)
{
	if (KMessageBox::questionYesNo(this, i18n("A new version of Circuit Macros (version %1) is available. Do you want to upgrade?").arg(version), i18n("Upgrade")) == KMessageBox::Yes)
	{
		cmm->downloadLatest();
	}
}

void MainWindow::circuitMacrosConfigured()
{
	statusBar()->showMessage(i18n("Ready"), 5000);
}

void MainWindow::setCurrentLineNumber()
{
	QTextCursor cursor      = textArea->textCursor();

	// Current line text
	// QString cur_line_text   = cursor.block().text().trimmed();

	// Current line
	int     cur_line_number = cursor.blockNumber() + 1;

	// Current column
	int     cur_line_column = cursor.columnNumber() + 1;

		
	lineNumberLabel->setText(QString("Line number: %1, Column number: %2").arg(cur_line_number).arg(cur_line_column));
}


