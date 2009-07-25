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
    
    QPixmap* pixmap() {return &_pixmap;}

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
