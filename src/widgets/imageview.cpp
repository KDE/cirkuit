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
    m_scaleFactor = 1.0;
    m_imageLabel->adjustSize();
}

void ImageView::clear()
{
    m_image = QImage();
    m_imageLabel->setPixmap(QPixmap());
}

