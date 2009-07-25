#ifndef EXTERNALBINMANAGER_H
#define EXTERNALBINMANAGER_H

#include <QObject>
#include <QStringList>

class ExternalBinManager : public QObject
{
	Q_OBJECT

	public:
		ExternalBinManager();

		bool checkAll() const;
		QStringList missingApps() const;

		QStringList neededApps() const { return _neededApps; }

		bool checkExistence(const QString& appname) const;
		bool checkExistence(const QStringList& appnames) const;

	private:
		QStringList _neededApps;

		bool checkPresenceInDir(const QString& appname, const QString& dirname) const;
};

#endif // EXTERNALBINMANAGER_H
