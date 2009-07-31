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

#ifndef QIMAGEDISPLAY_H
#define QIMAGEDISPLAY_H

#include <qwidget.h>

/**
	@author Matteo Agostinelli <agostinelli@gmail.com>
*/
class QImageDisplay : public QWidget
{
    Q_OBJECT
public:
    QImageDisplay(QWidget* parent = 0);

    ~QImageDisplay();

    QPixmap* pixmap() {
        return &_pixmap;
    }

public slots:
    void setImage(const QImage&);
    void clear();

    void setFastTransformation(bool fast = false);

private:
    QPixmap _pixmap;
    bool _fastTransform;

protected:
    void paintEvent(QPaintEvent* event);
};

#endif
