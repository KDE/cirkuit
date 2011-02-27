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

class KActionCollection;
class RenderThread;
class QGraphicsPixmapItem;
class QLabel;
class QTimer;

class KAction;
class KToggleAction;

class ImageView: public QGraphicsView
{
    Q_OBJECT
public:
    ImageView(QWidget* parent = 0);
    virtual ~ImageView();
    
    double scaleFactor() const;
    bool fitMode() const;
    
public slots:
    void setImage(const QImage& image, bool firstTime = false);
    void setPdfUrl(const QString& pdfUrl);
    void setFitMode(bool enabled);
    
    void clear();
    
    void zoomIn();
    void zoomOut();
    void zoomFit();
    void zoomFit(const QPixmap& pixmap);
    void normalSize();
    
    KAction* zoomFitPageAction() const;
    KAction* zoomFitAction() const;
    KAction* zoomInAction() const;
    KAction* zoomOutAction() const;
    KAction* actualSizeAction() const;
        
    void setupActions(KActionCollection* actionCollection);
    void updateZoomToFit();
    
private slots:
    void scaleImage(double factor);
    void trigger();    
    
signals:
    void enableZoomIn(bool);
    void enableZoomOut(bool);
    void fitModeChanged(bool);
    
protected:
    virtual void contextMenuEvent(QContextMenuEvent* event);
    virtual void resizeEvent(QResizeEvent*);
    virtual void wheelEvent(QWheelEvent* event);
    
private:
    QImage m_image;
    QString m_pdfUrl;

    QGraphicsScene* m_scene;
    QGraphicsPixmapItem* m_pixmap;
    RenderThread* m_render;
    QTimer* m_timer;
    double m_ratio;
    bool m_fitMode;
    
    double m_scaleFactor, m_scaleMin, m_scaleMax;
    
    KToggleAction* m_zoomFitPageAction;
    KAction* m_zoomFitAction, *m_zoomInAction, *m_zoomOutAction, *m_actualSizeAction;
};

#endif // IMAGEVIEW_H
