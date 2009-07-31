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

#ifndef HTTPDOWNLOADER_H
#define HTTPDOWNLOADER_H

#include <QObject>
#include <QHttp>
#include <QQueue>
#include <QUrl>
#include <QPair>
#include <QMap>

typedef QPair<QUrl, QIODevice*> Download;

class HttpDownloader : public QObject
{
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

#endif // HTTPDOWNLOADER_H
