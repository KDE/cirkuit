#ifndef LIVEPREVIEWWIDGET_H
#define LIVEPREVIEWWIDGET_H

#include <QDockWidget>

class QImageDisplay;
class QImage;
class QTimer;

class LivePreviewWidget : public QDockWidget
{
  Q_OBJECT
  public:
    LivePreviewWidget(const QString & title, QWidget * parent = 0, Qt::WindowFlags flags = 0);
  
  private:
    QImageDisplay* imageDisplay;
    QTimer* timer;
    
  public slots:
    void setImage(const QImage&);
    void clear();
    
    void setSmoothTransformation();
    
  protected:
//     void dragEnterEvent ( QDragEnterEvent * event );
//     void dragLeaveEvent ( QDragLeaveEvent * event );
//     void moveEvent ( QMoveEvent * event );
    void resizeEvent ( QResizeEvent * event );
};

#endif
