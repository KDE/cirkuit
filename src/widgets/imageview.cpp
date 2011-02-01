/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  Matteo Agostinelli <matteo.agostinelli@uni-klu.ac.at>

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

#include "imageview.h"
#include "renderthread.h"

#include <QLabel>
#include <QScrollBar>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QKeyEvent>

#include <KDebug>

ImageView::ImageView(QWidget* parent): QGraphicsView(parent), m_image(QImage()), m_pdfUrl(QString())
{
    m_scene = new QGraphicsScene(this);
    m_pixmap = m_scene->addPixmap(QPixmap::fromImage(m_image));
    setBackgroundRole(QPalette::Base);
    setScene(m_scene);
    setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);
    setDragMode(QGraphicsView::ScrollHandDrag);
    
    setMinimumWidth(100);
    setMinimumHeight(50);
    
    m_render = new RenderThread;
    connect(m_render, SIGNAL(previewReady(QImage)), this, SLOT(setImage(QImage)));
    
    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(zoomFit()));
 
    setFitMode(false);
    normalSize();
}

ImageView::~ImageView()
{
    delete m_imageLabel;
    delete m_scene;
}

void ImageView::setImage(const QImage& image)
{
    m_pixmap->setPixmap(QPixmap::fromImage(image));
    m_pixmap->update();
    setSceneRect(m_scene->itemsBoundingRect());
}

void ImageView::setPdfUrl(const QString& pdfUrl)
{
    m_pdfUrl = pdfUrl;
}

void ImageView::clear()
{
    m_image = QImage();
    m_pixmap->setPixmap(QPixmap());
    m_pixmap->update();
}

void ImageView::scaleImage(double factor)
{
    m_timer->stop();
    
    m_scaleFactor *= factor;
    m_render->generatePreview(m_pdfUrl, m_scaleFactor);
    
    emit enableZoomIn(m_scaleFactor < 3.5);
    emit enableZoomOut(m_scaleFactor > 0.1);    
}

void ImageView::normalSize()
{
    m_scaleFactor = 1.0;
    m_ratio = 1.0;
    scaleImage(1.0);
}

void ImageView::zoomIn()
{
    scaleImage(1.25);
}

void ImageView::zoomOut()
{
    scaleImage(0.8);
}

void ImageView::zoomFit()
{
    double hRatio = 1.00 * viewport()->width() / m_pixmap->pixmap().width();
    double vRatio = 1.00 * viewport()->height() / m_pixmap->pixmap().height();
    double ratio = qMin(hRatio, vRatio);
    double fraction = 1.0 * ratio / m_ratio;
    m_ratio = ratio;
    
    kDebug() << "Viewport: " << viewport()->size();
    kDebug() << "Pixmap: " << m_pixmap->pixmap().size();
    kDebug() << "New ratio: " << ratio;
    kDebug() << "Factor: " << m_scaleFactor;
    
    if (fraction > 0.99 && fraction < 1.01) {
        return;
    }
    
    scaleImage(ratio);
}

double ImageView::scaleFactor() const
{
    return m_scaleFactor;
}

void ImageView::resizeEvent(QResizeEvent* event)
{    
    if (event->oldSize().height() > 0 && !m_render->isRunning() && m_fitMode) {
        m_timer->start(100);
        return;
    }
     
    QGraphicsView::resizeEvent(event);
}

void ImageView::setFitMode(bool enabled)
{
    m_fitMode = enabled;
}

bool ImageView::fitMode() const
{
    return m_fitMode;
}


