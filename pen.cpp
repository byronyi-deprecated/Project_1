#include "pen.h"

Pen::Pen(QPaintDevice *paintDevice) :
    QPainter(paintDevice)
{
    pen.setBrush(brush);
    setPen(pen);
}

void Pen::paintByPress(QPoint p)
{
    drawPoint(p);
}

void Pen::setPenWidth(int w)
{
    pen.setWidth(w);
}

void Pen::setPenCapStyle(Qt::PenCapStyle c)
{
    pen.setCapStyle(c);
}

void Pen::setForegroundColor(QColor color)
{
    pen.setColor(color);
    brush.setColor(color);
}
