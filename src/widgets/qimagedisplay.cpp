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
#include <KDebug>

struct ResizerPrivate
{
    QSize size;
    Qt::AspectRatioMode aspectMode;
    QImage input;
};

Resizer::Resizer(QObject* parent): QObject(parent), d(new ResizerPrivate)
{
    d->aspectMode = Qt::KeepAspectRatio;
}

Resizer::~Resizer()
{
    delete d;
}

void Resizer::setAspectRatioMode(const Qt::AspectRatioMode mode)
{
    d->aspectMode = mode;
}

void Resizer::setSize(const QSize& size)
{
    d->size = size;
}

void Resizer::setInput(const QImage& input)
{
    d->input = input;
}

void Resizer::start()
{
    if ( d->input.isNull() || d->input.size().height() < d->size.height() || d->input.size().width() < d->size.width()) {
        emit error();
        return;       
    }
    
    kDebug() << "I am now resizing to " << d->size;

    QImage output = d->input.scaled( d->size, d->aspectMode, Qt::FastTransformation );
    emit finished( output );
}


QImageDisplay::QImageDisplay(QWidget* parent)
 : QWidget(parent), m_pixmap(QPixmap())
{
    setMinimumWidth(100);
    setMinimumHeight(50);
}

QImageDisplay::~QImageDisplay()
{
}

void QImageDisplay::setImage(const QImage& image)
{
    m_pixmap = QPixmap::fromImage(image);

    update();
}

void QImageDisplay::paintEvent(QPaintEvent* /*event*/)
{
    if (!m_pixmap) {
        return;
    }
    
    QPainter painter(this);

    int width = this->size().width();
    int height = this->size().height();

    int picWidth = m_pixmap.size().width();
    int picHeight = m_pixmap.size().height();

    // center the pixmap
    int x = 0;
    int y = 0;

    if (picHeight < height) {
        y = height / 2 - picHeight / 2;
    }

    if (picWidth < width) {
        x = width / 2 - picWidth / 2;
    }

    painter.drawPixmap(x, y, m_pixmap);
}

QPixmap* QImageDisplay::pixmap()
{
    return &m_pixmap;
}

void QImageDisplay::clear()
{
    m_pixmap = QPixmap();
    update();
}


