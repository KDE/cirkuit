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

#include "previewwidget.h"
#include "imageview.h"

#include <QImage>
#include <QTimer>


PreviewWidget::PreviewWidget(const QString & title, QWidget * parent, Qt::WindowFlags flags)
  : QDockWidget(title, parent, flags)
{
    m_imageView = new ImageView(this);
  
    setWidget(m_imageView);
    setMinimumHeight(100);
    setMinimumWidth(150);
}

void PreviewWidget::setImage(const QImage& image)
{
    m_imageView->setImage(image);
}

QSize PreviewWidget::sizeHint() const
{
    return QSize(300,150);
}

void PreviewWidget::clear()
{
    m_imageView->clear();
}

ImageView* PreviewWidget::view() const
{
    return m_imageView;
}



