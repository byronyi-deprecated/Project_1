#include "painter.h"

Painter::Painter(QWidget *parent) :
    QWidget(parent)
{
    setBackgroundRole(QPalette::Window);
    tool = null;
    createPaintDevice();
    this->setMouseTracking(true);
}

void Painter::createPaintDevice()
{
    pixmap = new QPixmap;
    painter = new QPainter(this);
    paintRect = new QRect(this->pos(), QSize(0, 0));

    brush = new QBrush;
    p = new QPen;
    p->setBrush(brush);
    painter->setPen(p);

    paintActions.clear();
    reDoActions.clear();
}

void Painter::clear()
{
    zoomFactor = 1.0;
    paintRect->setSize(pixmap->size() * zoomFactor);
    pixmap->fill(curBColor());
    paintActions.clear();
    reDoActions.clear();
}

bool Painter::readFile(QString fileName)
{
    if(!fileName.isEmpty())
    {
        pixmap->load(fileName);
        zoomFactor = 1.0;
        paintRect->setSize(pixmap->size());
        update();
    }
    return !fileName.isEmpty();
}

bool Painter::writeFile(QString fileName)
{
    QPainter savePainter(pixmap);
    zoomFactor = 1.0;
    for(QVector::iterator i = paintActions.begin();
        i != paintActions.end(); ++i)
    {
        i->play(savePainter);
    }
    return pixmap->save(fileName);
}

void Painter::unDo()
{
    if(paintActions.isEmpty()) return;
    reDoActions.append(paintActions.last());
    paintActions.pop_back();
}

void Painter::reDo()
{
    if(reDoActions.isEmpty()) return;
    paintActions.append(paintActions.last());
    reDoActions.pop_back();
}

void Painter::setZoomFactor(double z)
{
    if(z < 0) zoomFactor = 0.001; else zoomFactor = z;
    emit zoomFactorChanged();
    paintRect->setSize(pixmap->size() * zoomFactor);
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
        paintActions.clear();
        reDoActions.clear();
    }
    *pixmap = pixmap->scaled(size);
    paintRect->setSize(size);
    update();
    return true;
}
//to be done
void Painter::mousePressEvent(QMouseEvent *e)
{
    switch(tool) {
    case null:
        break;
    case pen:
        if(e->button() == Qt::LeftButton)
        {

            painter->drawPoint(e->pos() / zoomFactor);
            update();
        }
        if(e->button() == Qt::RightButton)
        {

        }
     case line:
        if(e->button() == Qt::LeftButton)
        {
            p.setBrush();
        }
    }
}
//to be done
void Painter::mouseDoubleClickEvent(QMouseEvent *e)
{

}
//to be done
void Painter::mouseMoveEvent(QMouseEvent *e)
{
    cursorPos = e->pos();
    emit cursorChanged();
}

void Painter::paintEvent(QPaintEvent * /* e */)
{
    if(!pixmap->isNull())
    {
        painter->drawPixmap((*paintRect), (*pixmap));
        for(QVector::iterator i = paintActions.begin();
            i != paintActions.end(); ++i)
        {
            i->play(painter);
        }
    }
}
