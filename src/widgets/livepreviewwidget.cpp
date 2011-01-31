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

#include "livepreviewwidget.h"
#include "imageview.h"

#include <QImage>
#include <QTimer>


LivePreviewWidget::LivePreviewWidget(const QString & title, QWidget * parent, Qt::WindowFlags flags)
  : QDockWidget(title, parent, flags)
{
    m_imageView = new ImageView(this);
  
    m_timer = new QTimer;
    m_timer->setSingleShot(true);
    m_timer->setInterval(100);
  
    connect(m_timer, SIGNAL(timeout()), this, SLOT(setSmoothTransformation()));
  
    setWidget(m_imageView);
    setMinimumHeight(180);
    setMinimumWidth(150);
}

void LivePreviewWidget::setImage(const QImage& image)
{
    setSmoothTransformation();
    m_imageView->setImage(image);
}

void LivePreviewWidget::clear()
{
    m_imageView->clear();
}

void LivePreviewWidget::resizeEvent (QResizeEvent* event)
{
    Q_UNUSED(event)
    //m_imageView->setFastTransformation(true);
  
    m_timer->start();
}

void LivePreviewWidget::setSmoothTransformation()
{
    //m_imageView->setFastTransformation(false);
}

