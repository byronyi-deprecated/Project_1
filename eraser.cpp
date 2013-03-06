#include "eraser.h"

Eraser::Eraser(QPaintDevice *paintDevice) :
    QPainter(paintDevice)
{
    cursor = QPixmap(QSize(1, 1));
    cursor.fill();
}

void Eraser::paintByPress(QPoint p)
{
    QRect rect(p.x() - cursor.width() / 2,
               p.y() - cursor.height() / 2,
               cursor.width(), cursor.height());
    drawPixmap(rect, cursor);
}

void Eraser::setEraserSize(int s)
{
    cursor.scaled(QSize(s, s));
}

void Eraser::setBackgroundColor(QColor c)
{
    cursor.fill(c);
}
