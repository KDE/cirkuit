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

#include <QLabel>
#include <QScrollBar>

ImageView::ImageView(QWidget* parent): QScrollArea(parent), m_image(QImage())
{
    m_imageLabel = new QLabel;
    m_imageLabel->setBackgroundRole(QPalette::Base);
    m_imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    m_imageLabel->setScaledContents(true);
    
    setBackgroundRole(QPalette::Base);
    setWidget(m_imageLabel);
    setAlignment(Qt::AlignCenter);
    
    setMinimumWidth(100);
    setMinimumHeight(50);
}

ImageView::~ImageView()
{

}

void ImageView::setImage(const QImage& image)
{
    m_image = image;
    
    if (image.isNull()) {
        return;
    }
    
    m_imageLabel->setPixmap(QPixmap::fromImage(m_image));
    normalSize();
}

void ImageView::clear()
{
    m_image = QImage();
    m_imageLabel->setPixmap(QPixmap());
}

void ImageView::adjustScrollBar(QScrollBar* scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value() + ((factor - 1) * scrollBar->pageStep()/2)));
}

void ImageView::scaleImage(double factor)
{
    Q_ASSERT(m_imageLabel->pixmap());
    m_scaleFactor *= factor;
    m_imageLabel->resize(m_scaleFactor * m_imageLabel->pixmap()->size());

    adjustScrollBar(this->horizontalScrollBar(), factor);
    adjustScrollBar(this->verticalScrollBar(), factor);
    
    emit enableZoomIn(m_scaleFactor < 1.5);
    emit enableZoomOut(m_scaleFactor > 0.5);
}

void ImageView::normalSize()
{
    m_imageLabel->adjustSize();
    m_scaleFactor = 1.0;
}

void ImageView::zoomIn()
{
    scaleImage(1.25);
}

void ImageView::zoomOut()
{
    scaleImage(0.8);
}

