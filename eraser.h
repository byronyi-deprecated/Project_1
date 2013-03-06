#ifndef ERASER_H
#define ERASER_H

#include <QPainter>
#include <QColor>
#include <QMouseEvent>
#include <QSize>
#include <QCursor>

class Eraser : public QPainter
{
    Q_OBJECT
public:
    explicit Eraser(QObject *parent = 0);
    
signals:
    
public slots:
    void paintByPress(QPicture*, QMouseEvent*);
    void setEraserSize(int );
    void setBackgroundColor(QColor );
private:
    QColor backgroundColor;
    QSize size;
    QPixmap cursor;
};

#endif // ERASER_H
