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
#include "renderthread.h"

#include <QLabel>
#include <QScrollBar>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QKeyEvent>
#include <QMenu>

#include "cirkuit_debug.h"
#include <KAction>
#include <KToggleAction>
#include <KActionCollection>
#include <KIcon>
#include <KLocale>

ImageView::ImageView(QWidget* parent): QGraphicsView(parent), m_image(QImage()), m_pdfUrl(QString())
{
    m_scene = new QGraphicsScene(this);
    m_pixmap = m_scene->addPixmap(QPixmap::fromImage(m_image));
    setBackgroundRole(QPalette::Base);
    setScene(m_scene);
    setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);
    setDragMode(QGraphicsView::ScrollHandDrag);
    
    setMinimumWidth(100);
    setMinimumHeight(50);
    
    m_render = new RenderThread;
    connect(m_render, SIGNAL(previewReady(QImage)), this, SLOT(setImage(QImage)));
    
    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(zoomFit()));
 
    setFitMode(false);
    normalSize();
    
    m_scaleMin = 0.1;
    m_scaleMax = 5.0;
}

ImageView::~ImageView()
{
    delete m_render;
    delete m_timer;
    delete m_pixmap;
}

void ImageView::setupActions(KActionCollection* actionCollection)
{    
    m_zoomInAction = KStandardAction::zoomIn(this, SLOT(zoomIn()), actionCollection);
    m_zoomOutAction = KStandardAction::zoomOut(this, SLOT(zoomOut()), actionCollection);
    m_zoomFitAction = KStandardAction::fitToPage(this, SLOT(zoomFit()), actionCollection);
    m_zoomFitAction->setIcon(KIcon("zoom-fit-best"));
    m_actualSizeAction = KStandardAction::actualSize(this, SLOT(normalSize()), actionCollection);
    
    connect(this, SIGNAL(enableZoomIn(bool)), m_zoomInAction, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(enableZoomOut(bool)), m_zoomOutAction, SLOT(setEnabled(bool)));
    
    m_zoomFitPageAction = new KToggleAction(i18n("Zoom to fit"), 0);
    m_zoomFitPageAction->setShortcut(Qt::CTRL + Qt::Key_0);
    m_zoomFitPageAction->setIcon(KIcon("zoom-fit-best"));
    actionCollection->addAction( "view_zoom_to_fit", m_zoomFitPageAction);
    connect(m_zoomFitPageAction, SIGNAL(triggered()), this, SLOT(updateZoomToFit()));
    connect(this, SIGNAL(fitModeChanged(bool)), m_zoomFitPageAction, SLOT(setChecked(bool)));
    connect(this, SIGNAL(fitModeChanged(bool)), this, SLOT(updateZoomToFit()));
    updateZoomToFit();
    
    // add actions to the widget's list for the popup menu
    addAction(m_zoomInAction);
    addAction(m_zoomOutAction);
    addAction(m_actualSizeAction);
    addAction(m_zoomFitAction);
    addAction(m_zoomFitPageAction);
}

QAction* ImageView::zoomFitAction() const
{
    return m_zoomFitAction;
}

QAction* ImageView::zoomFitPageAction() const
{
    return m_zoomFitPageAction;
}

QAction* ImageView::zoomInAction() const
{
    return m_zoomInAction;
}

QAction* ImageView::zoomOutAction() const
{
    return m_zoomOutAction;
}

QAction* ImageView::actualSizeAction() const
{
    return m_actualSizeAction;
}

void ImageView::updateZoomToFit()
{
    m_zoomFitAction->setEnabled(!m_zoomFitPageAction->isChecked());
    setFitMode(m_zoomFitPageAction->isChecked());
}

void ImageView::setImage(const QImage& image, bool firstTime)
{
    if (fitMode() && firstTime) {
        // if the image should fit to page then the first time resize it
        // and then display it
        zoomFit(QPixmap::fromImage(image));
    } else {
        m_pixmap->setPixmap(QPixmap::fromImage(image));
        m_pixmap->update();
        setSceneRect(m_scene->itemsBoundingRect());
    }
}

void ImageView::setPdfUrl(const QString& pdfUrl)
{
    m_pdfUrl = pdfUrl;
}

void ImageView::clear()
{
    m_image = QImage();
    m_pixmap->setPixmap(QPixmap());
    m_pixmap->update();
    m_scaleFactor = 1.0;
    m_ratio = 1.0;
}

void ImageView::scaleImage(double factor)
{
    m_timer->stop();
    
    m_scaleFactor *= factor;
    qBound<double>(m_scaleMin, m_scaleFactor, m_scaleMax);
    m_render->generatePreview(m_pdfUrl, m_scaleFactor);
    
    emit enableZoomIn(m_scaleFactor <= m_scaleMax);
    emit enableZoomOut(m_scaleFactor >= m_scaleMin);    
}

void ImageView::normalSize()
{
    setFitMode(false);
    m_scaleFactor = 1.0;
    m_ratio = 1.0;
    scaleImage(1.0);
}

void ImageView::zoomIn()
{
    if (m_scaleFactor >= m_scaleMax) {
        return;
    }
    
    setFitMode(false);
    scaleImage(1.25);
}

void ImageView::zoomOut()
{
    if (m_scaleFactor <= m_scaleMin) {
        return;
    }
    
    setFitMode(false);
    scaleImage(0.8);
}

void ImageView::zoomFit()
{
    zoomFit(m_pixmap->pixmap());
}

void ImageView::zoomFit(const QPixmap& pixmap)
{
    if (pixmap.height() == 0 || viewport()->height() == 0) {
        return;
    }
    
    double hRatio = 1.00 * viewport()->width() / pixmap.width();
    double vRatio = 1.00 * viewport()->height() / pixmap.height();
    double ratio = qMin(hRatio, vRatio);
    double fraction = 1.0 * ratio / m_ratio;
    m_ratio = ratio;
    
    if (fraction > 0.99 && fraction < 1.01) {
        // no resize is needed but re-center the pixmap anyway
        setSceneRect(m_scene->itemsBoundingRect());
        return;
    }
    
    scaleImage(ratio);
}

double ImageView::scaleFactor() const
{
    return m_scaleFactor;
}

void ImageView::resizeEvent(QResizeEvent* event)
{    
    if (event->oldSize().height() > 0 && !m_render->isRunning() && m_fitMode) {
        trigger();
        return;
    }
     
    QGraphicsView::resizeEvent(event);
}

void ImageView::setFitMode(bool enabled)
{
    if (m_fitMode != enabled) {
        m_fitMode = enabled;
        if (m_fitMode) zoomFit();
        emit fitModeChanged(enabled);
    }    
}

bool ImageView::fitMode() const
{
    return m_fitMode;
}

void ImageView::trigger()
{
    m_timer->start(50);
}

void ImageView::wheelEvent(QWheelEvent* event)
{
    if (event->modifiers() == Qt::ControlModifier) {
        if (event->delta() > 0) {
            zoomIn();
        } else {
            zoomOut();
        }
    }
}

void ImageView::contextMenuEvent(QContextMenuEvent* event)
{
    QMenu *menu = new QMenu(this);
    menu->addActions(actions());
    menu->exec(event->globalPos());
    menu->deleteLater();
}
