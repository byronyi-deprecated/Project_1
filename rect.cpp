#include "rect.h"

Rect::Rect(QPaintDevice *paintDevice) :
    QPainter(paintDevice)
{
    pen.setBrush(brush);
}

void Rect::paintByPress(QPoint start, QPoint end)
{
    switch(drawType){
    case 1:
        drawRect(QRect(start, end));
        break;
    case 2:
        drawRoundedRect(QRect(start, end), 50, 50,
                        Qt::RelativeSize);
    case 3:
        drawEllipse(QRect(start, end));
    }
}

void Rect::setDrawType(int i)
{
    drawType = i;
}

void Rect::setFillStyle(Qt::BrushStyle b)
{
    brush.setStyle(b);
}

void Rect::setBoundaryStyle(Qt::PenStyle s)
{
    pen.setStyle(s);
}

void Rect::setBoundaryJoinStyle(Qt::PenJoinStyle j)
{
    pen.setJoinStyle(j);
}

void Rect::setFillColor(bool f)
{
    if(f)
        brush.setColor(foregroundColor);
    else
        brush.setColor(backgroundColor);
}

void Rect::setBoundaryWidth(int w)
{
    pen.setWidth(w);
}
