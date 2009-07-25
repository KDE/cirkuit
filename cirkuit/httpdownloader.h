#ifndef __HTTPDOWNLOADER_H
#define __HTTPDOWNLOADER_H
#include <QHttp>
#include <QQueue>
#include <QUrl>
#include <QPair>
#include <QMap>

class MiniSpy : public QObject {
  Q_OBJECT
public:
  MiniSpy(QObject *sndr, const char *sign, QObject *parent=0) : QObject(parent) {
	connect(sndr, sign, SLOT(execute(const QUrl &)));
  }
public slots:
  void execute(const QUrl &u){
	qDebug("Finished: %s", qPrintable(u.toString()));
  }
};


typedef QPair<QUrl, QIODevice*> Download;

class HttpDownloader : public QObject {
  Q_OBJECT
  Q_PROPERTY( int concurrentLimit
              READ concurrentLimit
              WRITE setConcurrentLimit )
public:
  HttpDownloader(QObject *parent=0);
  ~HttpDownloader();
  void addDownload(const QUrl &url, QIODevice *device);
  int concurrentLimit() const;
public slots:
  void setConcurrentLimit(int);
signals:
  void finished(const QUrl &url, bool err);
  void done();
  void progress(int,int);
  void concurrentLimitChanged(int);
private:
  QMap<QHttp*, QUrl> m_objects;
  QQueue<Download> m_pending;
  int m_concurrentlimit;
  void spawnDownloader();
  void startRequert(QHttp *http);
private slots:
  void requestFinished(int request, bool err);
  void objectDone(bool err);
};
#endif
