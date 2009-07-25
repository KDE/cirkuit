#include "livepreviewwidget.h"
#include "qimagedisplay.h"

#include <QImage>
#include <KMessageBox>
#include <QDebug>
#include <QTimer>

#include <QMoveEvent>

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

