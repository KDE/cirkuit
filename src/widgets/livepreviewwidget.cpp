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
#include <QThread>
#include <QKeyEvent>

#include <KDebug>

LivePreviewWidget::LivePreviewWidget(const QString & title, QWidget * parent, Qt::WindowFlags flags)
  : QDockWidget(title, parent, flags), m_thread(0)
{
    m_imageDisplay = new QImageDisplay(this);
    m_imageDisplay->setBackgroundRole(QPalette::Base);
    
    setWidget(m_imageDisplay);
    setMinimumHeight(180);
    setMinimumWidth(150);
    
    m_resizer = new Resizer;
}

void LivePreviewWidget::setImage(const QImage& image)
{
    m_resizer->setInput(image);
    m_imageDisplay->setImage(image);
}

void LivePreviewWidget::clear()
{
    m_imageDisplay->clear();
}

void LivePreviewWidget::resizeEvent ( QResizeEvent* event )
{
    kDebug() << "Resize event";
    
    if (m_imageDisplay->pixmap() == 0) {
        return;
    }
    
    if (m_thread && m_thread->isRunning()) {
        kDebug() << "A thread is running";
        //return;
    }
    
    delete m_thread;
    m_thread = new QThread();
    m_resizer->moveToThread(m_thread);
    
    connect( m_thread, SIGNAL(started()), m_resizer, SLOT(start()) );
    connect( m_resizer, SIGNAL(finished(const QImage &)), m_imageDisplay, SLOT(setImage(const QImage &)) );
    
    m_resizer->setSize(event->size()); 
    kDebug() << "Resize event starting";
    m_thread->start();
    
    QWidget::resizeEvent ( event );
}

