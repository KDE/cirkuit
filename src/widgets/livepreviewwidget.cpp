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
#include "qimagedisplay.h"

#include <QImage>
#include <QTimer>


LivePreviewWidget::LivePreviewWidget(const QString & title, QWidget * parent, Qt::WindowFlags flags)
  : QDockWidget(title, parent, flags)
{
  imageDisplay = new QImageDisplay(this);
  imageDisplay->setBackgroundRole(QPalette::Base);
  
  timer = new QTimer;
  timer->setSingleShot(true);
  timer->setInterval(100);
  
  connect(timer, SIGNAL(timeout()), this, SLOT(setSmoothTransformation()));
  
  setWidget(imageDisplay);
  setMinimumHeight(180);
  setMinimumWidth(150);
}

void LivePreviewWidget::setImage(const QImage& image)
{
  setSmoothTransformation();
  imageDisplay->setImage(image);
}

void LivePreviewWidget::clear()
{
  imageDisplay->clear();
}

void LivePreviewWidget::resizeEvent ( QResizeEvent* /*event*/ )
{
  imageDisplay->setFastTransformation(true);
  
  timer->start();
}

void LivePreviewWidget::setSmoothTransformation()
{
  imageDisplay->setFastTransformation(false);
}

