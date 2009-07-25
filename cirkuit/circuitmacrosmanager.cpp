#include "circuitmacrosmanager.h"

#include <KStandardDirs>
#include <KTar>
#include <KNotification>
#include <KLocale>

#include <QFile>
#include <QUrl>
#include <QHttp>
#include <QDebug>
#include <QMessageBox>
#include <QtNetwork>
#include <QProcess>
#include <QBuffer>
#include "httpdownloader.h"

CircuitMacrosManager::CircuitMacrosManager(): QObject()
{
	progressNotify = new KNotification("Download progress");
	progressNotify->setComponentData(KComponentData("cirkuit"));
}

bool CircuitMacrosManager::checkExistence() const
{
	QString cm_path = KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/libcct.m4", true);

	if (QFile::exists(cm_path))
		return true;
	else
		return false;
}

void CircuitMacrosManager::downloadLatest()
{
	QString filename = KStandardDirs::locateLocal("data", "cirkuit/Circuit_macros.tar.gz", true);
	file = new QFile(filename);

	if (!file->open(QIODevice::WriteOnly))
	{
		 QMessageBox::information(0, tr("HTTP"),
								  tr("Unable to save the file %1: %2.")
								  .arg(filename).arg(file->errorString()));
		 delete file;
		 file = 0;
		 return;
	}
	
	dnldr = new HttpDownloader;
	MiniSpy spy(dnldr, SIGNAL(finished(const QUrl &, bool)));
	connect(dnldr, SIGNAL(done()), this, SLOT(done()));
	connect(dnldr, SIGNAL(progress(int,int)), this, SLOT(progress(int,int)));
	progressNotify->setText(i18n("Circuit Macros download in progress... please wait"));
	progressNotify->sendEvent();
	
	dnldr->addDownload(QUrl(QString("http://www.ece.uwaterloo.ca/~aplevich/Circuit_macros/Circuit_macros.tar.gz")), file);
}

void CircuitMacrosManager::done()
{
	qDebug("DONE");
	qDebug() << "Circuit macros downloaded";
	
	progressNotify->setText(i18n("Circuit Macros download finished"));
	progressNotify->sendEvent();

	file->close();

	KTar tarfile(file->fileName());
	tarfile.open(QIODevice::ReadOnly);
	qDebug() << "TARNAME: " << tarfile.fileName();
	const KArchiveDirectory* root = tarfile.directory();
	qDebug() << "ENTRIES: " << root->entries();
	qDebug() << "IS_DIR: " << root->isDirectory();

	const KArchiveDirectory* mainDir = (KArchiveDirectory*) root->entry(root->entries().at(0));
	qDebug() << "ENTRIES: " << mainDir->entries();
	mainDir->copyTo(KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/", true), true);
	
	configureCircuitMacros();
	installCctBatch();

	delete file;
	file = 0;
	
	progressNotify->setText(i18n("Circuit Macros download finished!"));
	progressNotify->sendEvent();


	emit(configured());
}

void CircuitMacrosManager::progress(int done, int total)
{	
	//qDebug() << "Progress: " << 100*done/total;
	
	if (100*done/total % 10 == 0)
	{
		progressNotify->setText(i18n("Circuit Macros download in progress... %1\% complete").arg(100*done/total));
		progressNotify->sendEvent();
	}
}


void CircuitMacrosManager::readmeDone()
{
	buffer->close();

	QString onlineVersion = findVersion(barray);
	qDebug() << "ONLINE version: " << onlineVersion;

	if (onlineVersion > installedVersion())
		emit newVersionAvailable(onlineVersion);

	delete buffer;
	buffer = 0;
}

void CircuitMacrosManager::configureCircuitMacros()
{
	QString homelibFilename = KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/homelib.txt", false);
	QString defineString = QString("`define(`HOMELIB_',`%1')')").arg(KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/", false));

	QFile homelibFile(homelibFilename);
	if (!homelibFile.open(QIODevice::WriteOnly | QIODevice::Text))
		 return;

	QTextStream out(&homelibFile);
	out << defineString << "\n";

	homelibFile.close();

	QStringList args;
	args << "homelib" << "psdefault";
	QProcess::startDetached("make", args, KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/", false));

	QFile::remove(KStandardDirs::locateLocal("data", "cirkuit/Circuit_macros.tar.gz", false));
	
	QString copySource = KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/boxdims.sty", false);
	QString copyDest = KStandardDirs::locateLocal("data", "cirkuit/build/boxdims.sty", false);
	qDebug() << copySource;
	qDebug() << copyDest;
	if (!QFile::copy(copySource, copyDest))
	{
		qDebug() << "copied";
		return;
	}

	qDebug() << "Circuit macros configured";
}

QString CircuitMacrosManager::installedVersion() const
{
	if (!checkExistence())
		return "";

	QString filename = KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/README", false);

	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return "";

	return findVersion(file.readAll());
}

void CircuitMacrosManager::checkOnlineVersion()
{
	barray.clear();
	buffer = new QBuffer(&barray);
	buffer->open(QIODevice::WriteOnly);

	dnldr = new HttpDownloader;
	connect(dnldr, SIGNAL(done()), this, SLOT(readmeDone()));
	dnldr->addDownload(QUrl(QString("http://www.ece.uwaterloo.ca/~aplevich/Circuit_macros/README")), buffer);
}

QString CircuitMacrosManager::findVersion(const QByteArray& byteArray) const
{
	bool versionStringFound = false;

	QRegExp rx("Version (\\d\\.\\d+)");
	QString version = "";

	QString content(byteArray);

	if (content.contains(rx))
	{
		versionStringFound = true;
		version = rx.cap(1);
	}

	return version;
}

void CircuitMacrosManager::installCctBatch()
{
	QString filename = KStandardDirs::locateLocal("data", "cirkuit/build/cctdpic", true);

	QFile file(filename);
	if (!file.open(QFile::WriteOnly | QFile::Text))
		return;

	QTextStream out(&file);

	out << "#!/bin/bash" << endl;
	out << "TMPNAME=tempA1R2C3W4i5e6r6d7" << endl;
	out << "CIRCUIT_MACROS_PATH=" << KStandardDirs::locateLocal("data", "cirkuit/circuit_macros") << endl << endl;

	out << "function mkltx()\n"
	"{\n"
	"cat > $TMPNAME.tex << EOF\n"
	"\\documentclass{article}\n"
	"\\usepackage{pstricks,pst-eps,boxdims,graphicx,ifpdf,pst-grad}\n"
	"\\pagestyle{empty}\n"
	"\\thispagestyle{empty}\n"
	"\\begin{document}\n"
	"\\newbox\\graph\n"
	"\\begin{TeXtoEPS}\n"
	"\\input $TMPNAME.cct\n"
	"\\box\n"
	"\\graph\n"
	"\\end{TeXtoEPS}\n"
	"\\end{document}\n"
	"EOF\n"
	"return\n"
	"}\n"
	"\n"
;

	out << "filpath=`dirname $1`\n"
"fn=$filpath/`basename $1 .cir`\n"
"if [ -e $fn.cir ]\n"
"then\n"
"m4 $CIRCUIT_MACROS_PATH/pstricks.m4 $CIRCUIT_MACROS_PATH/libcct.m4 $fn.cir | dpic -p > $TMPNAME.cct\n"
"if [ ! -e $TMPNAME.tex ]\n"
"then mkltx\n"
"fi\n"
"cp $TMPNAME.cct $fn.pst\n"
"latex $TMPNAME.tex -output-format=dvi\n"
"cp $TMPNAME.dvi $fn.dvi\n"
"dvips -Ppdf -G0 -E $TMPNAME -o $fn.eps\n"
"convert -density 200 $fn.eps $fn.png\n"
"\n"
"rm -f $TMPNAME.*\n"
"else\n"
"echo \"$fn.m4 does not exist!\"\n"
"fi\n"
;

	file.close();

	file.setPermissions(QFile::ExeOwner | QFile::ReadOwner | QFile::WriteOwner);
}
