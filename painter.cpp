#include "painter.h"

Painter::Painter(QWidget *parent) :
    QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

void Painter::clear()
{

}

bool Painter::readFile(QString fileName)
{
    return 1;
}

bool Painter::writeFile(QString fileName)
{
    return 1;
}

void Painter::unDo()
{

}

void Painter::reDo()
{

}

void Painter::zoomIn()
{

}

void Painter::zoomOut()
{

}

void Painter::mousePressEvent(QMouseEvent *)
{

}

void Painter::mouseDoubleClickEvent(QMouseEvent *)
{

}

void Painter::mouseMoveEvent(QMouseEvent *)
{

}

void Painter::paintEvent(QPaintEvent *)
{

}
