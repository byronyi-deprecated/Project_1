#ifndef ERASER_H
#define ERASER_H

#include <QPainter>
#include <QColor>
#include <QMouseEvent>
#include <QSize>
#include <QCursor>

class Eraser : public QPainter, public QObject
{
    Q_OBJECT
public:
    explicit Eraser(QPaintDevice *paintDevice = 0);
    
signals:
    
public slots:
    void paintByPress(QPoint );
    void setEraserSize(int );
    void setBackgroundColor(QColor );
private:
    QPixmap cursor;
};

#endif // ERASER_H
