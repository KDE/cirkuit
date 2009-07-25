#ifndef CIRCUITMACROSMANAGER_H
#define CIRCUITMACROSMANAGER_H

#include <QObject>
#include "httpdownloader.h"

class QFile;
class QBuffer;
class KNotification;

class CircuitMacrosManager : public QObject
{
	Q_OBJECT

	public:
		CircuitMacrosManager();

		bool checkExistence() const;
		void downloadLatest();

		QString installedVersion() const;
		void checkOnlineVersion();


	private slots:
		void done();
		void progress(int,int);
		void readmeDone();
		void installCctBatch();

		void configureCircuitMacros();
		QString findVersion(const QByteArray& byteArray) const;

	signals:
		void newVersionAvailable(const QString&);
		void configured();

	private:
		QFile* file;
		QBuffer* buffer;
		QByteArray barray;
		HttpDownloader* dnldr;
		
		KNotification* progressNotify;
};

#endif // CIRCUITMACROSMANAGER_H
