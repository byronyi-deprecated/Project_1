#include "painter.h"

Painter::Painter(QWidget *parent) :
    QWidget(parent)
{
    setBackgroundRole(QPalette::Window);
    tool = null;
    createPaintDevice();
    this->setMouseTracking(true);
    emit imageModified(false);
}

void Painter::createPaintDevice()
{
    pixmap = new QPixmap;
    painter = new QPainter;
    paintRect = new QRect(this->pos(), QSize(0, 0));

    brush = new QBrush(Qt::black);
    p = new QPen(Qt::black);
    p->setBrush(*brush);
    setBColor(Qt::white);

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
    QPixmap saveImage(*pixmap);
    QPainter savePainter(&saveImage);
    int tempZoomFactor(curZoomFactor());
    setZoomFactor(1.0);
    for(int i = 0; i < paintActions.count(); i++)
    {
        paintActions[i].play(&savePainter);
    }
    setZoomFactor(tempZoomFactor);
    return saveImage.save(fileName);
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
        emit imageModified(true);
    }
    *pixmap = pixmap->scaled(size);
    paintRect->setSize(size);
    update();
    return true;
}
//to be done
void Painter::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        switch(tool) {
        case pen:
        case line:
        case rect:
        case eraser:
        default: break;
        }
    }
    if(e->button() == Qt::RightButton)
    {
        penDialog = new PenDialog;
        switch(tool) {
        case pen:
            emit penSettings();
            break;
        case line:
            emit lineSettings();
            break;
        case rect:
            emit rectSettings();
            break;
        case eraser:
            emit eraserSettings();
            break;
        default: break;
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
    if(e->buttons() & Qt::LeftButton)
    {
        switch(tool) {
        case pen:
        case line:
        case rect:
        case eraser:
        default: break;
        }
    }
}

void Painter::paintEvent(QPaintEvent * /* e */)
{
    if(!pixmap->isNull())
    {
        painter->begin(this);
        painter->setPen(*p);
        painter->drawPixmap((*paintRect), (*pixmap));
        for(int i = 0; i < paintActions.count(); i++)
        {
            paintActions[i].play(painter);
        }
        painter->end();
    }
}

void Painter::setPenWidth(int ){}
void Painter::setPenCapStyle(Qt::PenCapStyle ){}

void Painter::setLineStyle(Qt::PenStyle ){}
void Painter::setLineCapStyle(Qt::PenCapStyle ){}
void Painter::setPolyLineEnabled(bool ){}
void Painter::setLineWidth(int ){}

void Painter::setDrawType(int ){}
void Painter::setFillStyle(Qt::BrushStyle ){}
void Painter::setBoundaryStyle(Qt::PenStyle ){}
void Painter::setBoundaryJoinStyle(Qt::PenJoinStyle ){}
void Painter::setFillColor(bool foregroundColor){}
void Painter::setBoundaryWidth(int ){}

void Painter::setEraserSize(int ){}
