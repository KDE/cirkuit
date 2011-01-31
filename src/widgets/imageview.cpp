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

void ImageView::adjustScrollBar(QScrollBar* scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value() + ((factor - 1) * scrollBar->pageStep()/2)));
}

void ImageView::scaleImage(double factor)
{
    m_scaleFactor *= factor;
    m_render->generatePreview(m_pdfUrl, m_scaleFactor);

    //adjustScrollBar(this->horizontalScrollBar(), factor);
    //adjustScrollBar(this->verticalScrollBar(), factor);
    
    emit enableZoomIn(m_scaleFactor < 3.5);
    emit enableZoomOut(m_scaleFactor > 0.1);    
}

void ImageView::normalSize()
{
    m_scaleFactor = 1.0;
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

double ImageView::scaleFactor() const
{
    return m_scaleFactor;
}
