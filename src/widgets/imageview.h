/*
    Copyright (C) 2011  Matteo Agostinelli <agostinelli@gmail.com>

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


#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QImage>
#include <QGraphicsView>

class RenderThread;
class QGraphicsPixmapItem;
class QLabel;
class QTimer;

class ImageView: public QGraphicsView
{
    Q_OBJECT
public:
    ImageView(QWidget* parent = 0);
    virtual ~ImageView();
    
    double scaleFactor() const;
    bool fitMode() const;
    
public slots:
    void setImage(const QImage& image);
    void setPdfUrl(const QString& pdfUrl);
    void setFitMode(bool enabled);
    
    void clear();
    
    void zoomIn();
    void zoomOut();
    void zoomFit();
    void normalSize();
    
private slots:
    void scaleImage(double factor);
    void trigger();
    
signals:
    void enableZoomIn(bool);
    void enableZoomOut(bool);
    void fitModeChanged(bool);
    
protected:
    void resizeEvent(QResizeEvent*);
    
private:
    QImage m_image;
    QString m_pdfUrl;
    QLabel* m_imageLabel;
    QGraphicsScene* m_scene;
    QGraphicsPixmapItem* m_pixmap;
    RenderThread* m_render;
    QTimer* m_timer;
    double m_ratio;
    bool m_fitMode;
    
    double m_scaleFactor;
};

#endif // IMAGEVIEW_H
