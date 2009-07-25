#include "circuitbuilder.h"

#include <QProcess>
#include <QImage>
#include <QStringList>
#include <QFileInfo>
#include <QDebug>
#include <KStandardDirs>
#include <KMessageBox>
#include <KLocalizedString>

#include "externalbinmanager.h"

CircuitBuilder::CircuitBuilder(const QString& interpreter)
  : QObject()
{
	if (interpreter.isEmpty())
		setPicInterpreter(KStandardDirs::locateLocal("data", "cirkuit/build/cctdpic", false));
	else
		setPicInterpreter(interpreter);
	
	mngr = new ExternalBinManager;
}

void CircuitBuilder::build(const KUrl& url, const QString& origDir)
{
	QStringList requiredApps;
	requiredApps << "latex" << "m4" << "dvips" << "convert";
	
	if (!checkApps(requiredApps))
		return;
	
	buildProcess = new QProcess;
	buildProcess->setWorkingDirectory(KStandardDirs::locateLocal("data", "cirkuit/build/", false));
	QStringList environment = QProcess::systemEnvironment();
	environment << QString("M4PATH=%1").arg(origDir);
	buildProcess->setEnvironment(environment);
	
	QFileInfo fileInfo(url.path());
	QStringList args;
	args << fileInfo.absolutePath() + "/" + fileInfo.baseName();
	qDebug() << "ARG: " + fileInfo.baseName();
  
	connect(buildProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(processFinished()));
	tempFileUrl = fileInfo.absolutePath() + "/" + fileInfo.baseName();
	buildProcess->start(mPicInterpreter, args);
}

void CircuitBuilder::processFinished()
{
  QImage image(tempFileUrl.path() + ".png");
  qDebug() << "OUTPUT: " + buildProcess->readAllStandardOutput();
  qDebug() << "OUTPUT: " + buildProcess->readAllStandardError();
  qDebug() << "PIC: " + tempFileUrl.path() + ".png";
  qDebug() << "BUILT";
  emit buildFinished();
  emit previewBuilt(image);
}

QString CircuitBuilder::epsFilePath() const
{
  return tempFileUrl.path() + ".eps";
}

QString CircuitBuilder::pdfFilePath() const
{
	QStringList requiredApps;
	requiredApps << "epstopdf";
	
	if (!checkApps(requiredApps))
		return "";
	
	QProcess pdfConvert;
	pdfConvert.setWorkingDirectory(KStandardDirs::locateLocal("data", "cirkuit/build/", false));
	pdfConvert.start("epstopdf", QStringList() << tempFileUrl.path() + ".eps");
	if (!pdfConvert.waitForStarted())
		return "";
	
	if (!pdfConvert.waitForFinished())
		return "";
	
	return tempFileUrl.path() + ".pdf";
}

QString CircuitBuilder::psFilePath() const
{
	QStringList requiredApps;
	requiredApps << "dvips";
	
	if (!checkApps(requiredApps))
		return "";
	
	QProcess pdfConvert;
	pdfConvert.setWorkingDirectory(KStandardDirs::locateLocal("data", "cirkuit/build/", false));
	//pdfConvert.start("epstopdf", QStringList() << "-d --nogs" << tempFileUrl.path() + ".eps" << "--outfile=" << tempFileUrl.path() + ".ps");
	pdfConvert.start("dvips", QStringList() << tempFileUrl.path() + ".dvi");
	if (!pdfConvert.waitForStarted())
		return "";
	
	if (!pdfConvert.waitForFinished())
		return "";
	
	qDebug() << "PS EXPORTED!";
	return tempFileUrl.path() + ".ps";
}

QString CircuitBuilder::svgFilePath() const
{
	QStringList requiredApps;
	requiredApps << "pdf2svg";
	
	if (!checkApps(requiredApps))
		return "";
	
	QProcess svgConvert;
	svgConvert.setWorkingDirectory(KStandardDirs::locateLocal("data", "cirkuit/build/", false));
	svgConvert.start("pdf2svg",  QStringList() << pdfFilePath() << tempFileUrl.path() + ".svg");
	if (!svgConvert.waitForStarted())
		return "";
	
	if (!svgConvert.waitForFinished())
		return "";
	
	return tempFileUrl.path() + ".svg";
}

QString CircuitBuilder::pngFilePath() const
{
  return tempFileUrl.path() + ".png";
}

QString CircuitBuilder::pstFilePath() const
{
  return tempFileUrl.path() + ".pst";
}

bool CircuitBuilder::checkApps(const QStringList& apps) const
{
	foreach (QString app, apps)
	{
		if (!mngr->checkExistence(app))
		{
			QMessageBox::critical(0, i18n("Error"), i18n("The following needed application is missing on your system: %1").arg(app));
			return false;
		}
	}
	
	return true;
}