#include "line.h"

Line::Line(QPaintDevice *paintDevice) :
    QPainter(paintDevice)
{
    pen.setBrush(brush);
    setPen(pen);
}

void Line::setLineStyle(Qt::PenStyle s)
{
    pen.setStyle(s);
}

void Line::setLineCapStyle(Qt::PenCapStyle c)
{
    pen.setCapStyle(c);
}

void Line::setLineWidth(int w)
{
    pen.setWidth(w);
}

void Line::setForegroundColor(QColor color)
{
    pen.setColor(color);
    brush.setColor(color);
}
