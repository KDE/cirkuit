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

#include "renderthread.h"

#include "poppler-qt5.h"

#include <QFile>
#include <QImage>
//#include <QDebug>

RenderThread::RenderThread(QObject* parent): QThread(parent)
{
 
    
}

RenderThread::~RenderThread()
{

    
}

void RenderThread::generatePreview(const QString& pdfUrl, double zoomFactor)
{
    m_pdfUrl = pdfUrl;
    m_zoomFactor = zoomFactor;
    
    start(LowPriority);
}

void RenderThread::run()
{
    double factor = qBound(0.01, m_zoomFactor, 10.0);
            
    if (!QFile::exists(m_pdfUrl)) return;

    Poppler::Document* document = Poppler::Document::load(m_pdfUrl);
    if (!document || document->isLocked()) {
        delete document;
        return;
    }

    // Access page of the PDF file
    document->setRenderHint(Poppler::Document::Antialiasing, true);
    document->setRenderHint(Poppler::Document::TextAntialiasing, true);
    Poppler::Page* pdfPage = document->page(0);  // Document starts at page 0
    if (pdfPage == 0) {
        return;
    }

    // Generate a QImage of the rendered page
    QImage image = pdfPage->renderToImage(factor*200.0, factor*200.0);
    emit previewReady(image);
    
    delete pdfPage;
    delete document;
}
