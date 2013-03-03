#include "painter.h"

Painter::Painter(QWidget *parent) :
    QWidget(parent)
{
    setBackgroundRole(QPalette::Window);
    pixmap = new QPixmap;
    rect = new QRect(this->pos(), QSize(0, 0));
    this->setMouseTracking(true);
}

void Painter::clear()
{
    zoomFactor = 1.0;
    rect->setSize(pixmap->size() * zoomFactor);
    pixmap->fill();
}

bool Painter::readFile(QString fileName)
{
    if(!fileName.isEmpty())
    {
        pixmap->load(fileName);
        zoomFactor = 1.0;
        rect->setSize(pixmap->size());
        update();
    }
    return !fileName.isEmpty();
}

bool Painter::writeFile(QString fileName)
{
    return pixmap->save(fileName);
}

void Painter::unDo()
{

}

void Painter::reDo()
{

}

void Painter::setZoomFactor(double z)
{
    if(z < 0) zoomFactor = 0.001; else zoomFactor = z;
    emit zoomFactorChanged();
    rect->setSize(pixmap->size() * zoomFactor);
    update();
}

bool Painter::setSize(QSize size)
{   
    if(size == curSize())
        return false;
    if(pixmap->isNull())
    {
        *pixmap = QPixmap(1, 1);
        pixmap->fill();
    }
    *pixmap = pixmap->scaled(size);
    rect->setSize(size);
    update();
    return true;
}

void Painter::mousePressEvent(QMouseEvent *e)
{

}

void Painter::mouseDoubleClickEvent(QMouseEvent *e)
{

}

void Painter::mouseMoveEvent(QMouseEvent *e)
{
    cursorPos = e->pos();
    emit cursorChanged();
}

void Painter::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    if(!pixmap->isNull())
    {
        p.drawPixmap((*rect), (*pixmap));
    }
}
