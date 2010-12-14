/***************************************************************************
*   Copyright (C) 2009 by Matteo Agostinelli                              *
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

#include "httpdownloader.h"

#include <KProtocolManager>

HttpDownloader::HttpDownloader(QObject *parent) : QObject(parent)
{
	m_concurrentlimit = 5;	
}

HttpDownloader::~HttpDownloader()
{
	
}

void HttpDownloader::addDownload(const QUrl &url, QIODevice *device)
{
	m_pending.enqueue(Download(url, device));
	if(m_objects.count()<m_concurrentlimit){
		spawnDownloader();
	}
}

int HttpDownloader::concurrentLimit() const
{
	return m_concurrentlimit;
}

void HttpDownloader::setConcurrentLimit(int v)
{
	if(v==m_concurrentlimit) return;
	m_concurrentlimit = v;
	emit concurrentLimitChanged(v);
	while(!m_pending.isEmpty() && m_objects.count()<m_concurrentlimit)
		spawnDownloader();
}

void HttpDownloader::spawnDownloader()
{
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

void HttpDownloader::requestFinished(int , bool err)
{
	QHttp *http = (QHttp*)sender();
	QIODevice *dev = http->currentDestinationDevice();
	if(dev){
		dev->close();
	}
	if(!m_objects[http].isValid()) return;
	emit finished(m_objects[http], err);
	m_objects[http] = QUrl();
}

void HttpDownloader::objectDone(bool)
{
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

void HttpDownloader::startRequert(QHttp *http)
{
	Download dnld = m_pending.dequeue();
	http->setHost(dnld.first.host(), dnld.first.port(80));
	m_objects[http] = dnld.first;
	http->get(dnld.first.path(), dnld.second);
}
