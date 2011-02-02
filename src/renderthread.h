/*
    Copyright (C) 2011  Matteo Agostinelli <agostinelli@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


#ifndef RENDERTHREAD_H
#define RENDERTHREAD_H

#include <QThread>

class QImage;

class RenderThread : public QThread
{
    Q_OBJECT
public:
    explicit RenderThread(QObject* parent = 0);
    virtual ~RenderThread();
    
public slots:
    void generatePreview(const QString& pdfUrl, double zoomFactor = 1.0);
    
signals:
    void previewReady(const QImage& image);
    
protected:
    void run();
     
private:
    QString m_pdfUrl;
    double m_zoomFactor;
};

#endif // RENDERTHREAD_H
