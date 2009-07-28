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

#include "qimagedisplay.h"

#include <QPainter>
#include <QDebug>

QImageDisplay::QImageDisplay(QWidget* parent)
 : QWidget(parent)
{
   setMinimumWidth(100);
   setMinimumHeight(50);
   
   setFastTransformation(false);
}

QImageDisplay::~QImageDisplay()
{
}

void QImageDisplay::setFastTransformation(bool fast)
{
  if(_fastTransform == fast)
    return;
  _fastTransform = fast;

  update();
}

void QImageDisplay::setImage(const QImage& image)
{
   _pixmap = QPixmap::fromImage(image);
   //setMaximumWidth(_pixmap.size().width());
   //setMaximumHeight(_pixmap.size().height());
   update();
}

void QImageDisplay::paintEvent(QPaintEvent* /*event*/)
{
   QPainter painter(this);

   int width = this->size().width();
   int height = this->size().height();

   int picWidth = _pixmap.size().width();
   int picHeight = _pixmap.size().height();
	
	//painter.fillRect(this->rect(), Qt::white);
   
   QPixmap scaledPixmap(_pixmap);

   if (picWidth > width || picHeight > height)
   {
      // scale pixmap to fit the widget
      if (_fastTransform)
        scaledPixmap = _pixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::FastTransformation);
      else
        scaledPixmap = _pixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);

      picWidth = scaledPixmap.size().width();
      picHeight = scaledPixmap.size().height();
   }

   // center the pixmap
   int x = 0;
   int y = 0;
   
   if (picHeight < height)
      y = height / 2 - picHeight / 2;
   
   if (picWidth < width)
      x = width / 2 - picWidth / 2;

   painter.drawPixmap(x, y, scaledPixmap);
}

void QImageDisplay::clear()
{
  _pixmap = QPixmap();
  //setMaximumWidth(_pixmap.size().width());
  //setMaximumHeight(_pixmap.size().height());
  update();
}


