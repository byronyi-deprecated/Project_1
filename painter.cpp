#include "painter.h"

Painter::Painter(QWidget *parent) :
    QWidget(parent)
{
    setBackgroundRole(QPalette::Window);
    tool = null;
    createPaintDevice();
    this->setMouseTracking(true);
    emit imageModified(false);
    backgroundColor = Qt::white;
}

void Painter::createPaintDevice()
{
    pixmap = new QPixmap;
    paintRect = new QRect(this->pos(), QSize(0, 0));

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

void Painter::setFColor(QColor curColor)
{
    pen->setForegroundColor(curColor);
    line->setForegroundColor(curColor);
    rect->setForegroundColor(curColor);
}

void Painter::setBColor(QColor curColor)
{
    rect->setBackgroundColor(curColor);
    eraser->setBackgroundColor(curColor);
    backgroundColor = curColor;
}

//to be done
void Painter::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        switch(tool) {
        case isPen:
        case isLine:
        case isRect:
        case isEraser:
        default: break;
        }
    }
    if(e->button() == Qt::RightButton)
    {
        switch(tool) {
        case isPen:
            emit penSettings();
            break;
        case isLine:
            emit lineSettings();
            break;
        case isRect:
            emit rectSettings();
            break;
        case isEraser:
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
        case isPen:
        case isLine:
        case isRect:
        case isEraser:
        default: break;
        }
    }
}

void Painter::paintEvent(QPaintEvent * /* e */)
{
    if(!pixmap->isNull())
    {
        QPainter painter;
        painter.begin(this);
        painter.drawPixmap((*paintRect), (*pixmap));
        for(int i = 0; i < paintActions.count(); i++)
        {
            paintActions[i].play(&painter);
        }
        painter.end();
    }
}

void Painter::setTool(int id)
{
    switch(id){
    case 1: tool = isPen; break;
    case 2: tool = isLine; break;
    case 3: tool = isRect; break;
    case 4: tool = isEraser; break;
    default: tool = tool; break;
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
