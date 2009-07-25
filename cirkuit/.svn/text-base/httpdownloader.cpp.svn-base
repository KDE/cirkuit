#include "httpdownloader.h"

#include <KProtocolManager>
#include <QDebug>

HttpDownloader::HttpDownloader(QObject *parent) : QObject(parent){
    m_concurrentlimit = 5;

	MiniSpy spy(this, SIGNAL(finished(const QUrl &, bool)));
}

HttpDownloader::~HttpDownloader()
{
	
}

void HttpDownloader::addDownload(const QUrl &url, QIODevice *device){
    m_pending.enqueue(Download(url, device));
    if(m_objects.count()<m_concurrentlimit){
        spawnDownloader();
    }
}

int HttpDownloader::concurrentLimit() const{
    return m_concurrentlimit;
}

void HttpDownloader::setConcurrentLimit(int v){
    if(v==m_concurrentlimit) return;
    m_concurrentlimit = v;
    emit concurrentLimitChanged(v);
    while(!m_pending.isEmpty() && m_objects.count()<m_concurrentlimit)
        spawnDownloader();
}

void HttpDownloader::spawnDownloader(){
    QHttp *http = new QHttp(this);

	// read KDE proxy settings
	if ( KProtocolManager::useProxy() )
	{
		KUrl proxyUrl = KProtocolManager::proxyFor("http");
		http->setProxy(proxyUrl.host(), proxyUrl.port());
	}

    connect(http, SIGNAL(requestFinished(int, bool)), SLOT(requestFinished(int, bool)));
	 connect(http, SIGNAL(dataReadProgress(int,int)), this, SIGNAL(progress(int,int)));
    connect(http, SIGNAL(done(bool)), SLOT(objectDone(bool)));
    m_objects[http] = QUrl();
    startRequert(http);
}

void HttpDownloader::requestFinished(int , bool err){
    QHttp *http = (QHttp*)sender();
    QIODevice *dev = http->currentDestinationDevice();
    if(dev){
        dev->close();
    }
    if(!m_objects[http].isValid()) return;
    emit finished(m_objects[http], err);
    m_objects[http] = QUrl();
}

void HttpDownloader::objectDone(bool){
    QHttp *http = (QHttp*)sender();
    if(m_pending.isEmpty()){
        m_objects.remove(http);
        http->deleteLater();
        if(m_objects.isEmpty())
          emit done();
        return;
    }
    startRequert(http);
}

void HttpDownloader::startRequert(QHttp *http){
    Download dnld = m_pending.dequeue();
    http->setHost(dnld.first.host(), dnld.first.port(80));
    m_objects[http] = dnld.first;
    http->get(dnld.first.path(), dnld.second);
}
