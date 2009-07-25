#include "externalbinmanager.h"

#include <QDebug>
#include <QFile>
#include <QDir>
#include <cstdlib>

ExternalBinManager::ExternalBinManager()
{
	_neededApps << "m4" << "latex" << "gs" << "dpic" << "dvips" << "epstopdf";
}

bool ExternalBinManager::checkExistence(const QString& appname) const
{
	QString pathEnv = getenv("PATH");
	QStringList pathDirs = pathEnv.split(":");

	bool found = false;
	foreach (QString dir, pathDirs)
		if (checkPresenceInDir(appname, dir))
			found = true;

	return found;
}

bool ExternalBinManager::checkExistence(const QStringList& appnames) const
{
	bool notFound = false;
	foreach (QString app, appnames)
		if (!checkExistence(app))
			notFound = true;

	return !notFound;
}

bool ExternalBinManager::checkAll() const
{
	foreach(QString app, _neededApps)
	{
		if (!checkExistence(app))
			return false;
	}

	return true;
}

QStringList ExternalBinManager::missingApps() const
{
	QStringList missing;

	foreach(QString app, _neededApps)
	{
		if (!checkExistence(app))
			missing << app;
	}

	return missing;
}

bool ExternalBinManager::checkPresenceInDir(const QString& appname, const QString& dirname) const
{
	QFileInfo fileinfo(QDir(dirname),appname);
	return fileinfo.exists();
}
