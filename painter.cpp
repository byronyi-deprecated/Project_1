#include "painter.h"
#include <QMessageBox>

Painter::Painter(QWidget *parent) :
    QWidget(parent)
{
    setBackgroundRole(QPalette::Window);
    tool = null;
    createPaintDevice();
    this->setMouseTracking(true);
    emit imageModified(false);
    foregroundColor = Qt::black;
    backgroundColor = Qt::white;
    eraserCursor.load(":/images/eraserCursor.bmp");
    eraserCursor = eraserCursor.scaled(QSize(10, 10));
//    QMessageBox::warning(this,"", QString::number(eraserCursor.width()));
}

void Painter::createPaintDevice()
{
    pixmap = new QPixmap;
    paintRect = new QRect(this->pos(), QSize(0, 0));

    paintActions.clear();
    reDoActions.clear();

    pen = new QPainter;
    line = new QPainter;
    rect = new QPainter;
    eraser = new QPainter;
}

void Painter::clear()
{
    zoomFactor = 1.0;
    paintRect->setSize(pixmap->size() * zoomFactor);
    pixmap->fill(curBColor());
    for(int i = 0; i < paintActions.size(); i++)
    {
        delete paintActions[i];
    }
    for(int i = 0; i < reDoActions.size(); i++)
    {
        delete paintActions[i];
    }
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
        paintActions[i]->play(&savePainter);
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

        for(int i = 0; i < paintActions.size(); i++)
        {
            delete paintActions[i];
        }
        for(int i = 0; i < reDoActions.size(); i++)
        {
            delete reDoActions[i];
        }
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
    foregroundColor = curColor;

    QPen ptemp;
    QBrush btemp;

    ptemp = pen->pen();
    ptemp.setColor(curColor);
    pen->setPen(ptemp);

    ptemp = line->pen();
    ptemp.setColor(curColor);
    line->setPen(ptemp);

    ptemp = rect->pen();
    ptemp.setColor(curColor);
    rect->setPen(ptemp);

    btemp = rect->brush();
    btemp.setColor((fillWithFColor) ? foregroundColor :
                                      backgroundColor);
    rect->setBrush(btemp);
}

void Painter::setBColor(QColor curColor)
{
    backgroundColor = curColor;

    QBrush btemp;

    btemp = rect->brush();
    btemp.setColor((fillWithFColor) ? foregroundColor :
                                  backgroundColor);
    rect->setBrush(btemp);
}

//to be done
void Painter::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        for(int i = 0; i < reDoActions.size(); i++)
        {
            delete reDoActions[i];
        }
        reDoActions.clear();

        QPicture *temp = new QPicture;
        paintActions.append(temp);

        switch(tool) {
        case isPen:
            pen->begin(temp);
            pen->drawPoint(e->pos() / zoomFactor);
        case isLine:
        case isRect:
        case isEraser:
        default: break;
        }
        update();
    }
    if(e->button() == Qt::RightButton)
    {
        switch(tool) {
        case isPen:
            emit pensettings();
            break;
        case isLine:
            emit linesettings();
            break;
        case isRect:
            emit rectsettings();
            break;
        case isEraser:
            emit erasersettings();
            break;
        default: break;
        }
    }
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
//to be done
void Painter::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->buttons() == Qt::LeftButton)
    {
        switch(tool) {
        case isPen: pen->end();
        case isLine:
        case isRect:
        case isEraser:
        default: break;
        }
    }
}

void Painter::mouseDoubleClickEvent(QMouseEvent *e)
{

}

void Painter::paintEvent(QPaintEvent * /* e */)
{
    if(!pixmap->isNull())
    {
        QPainter painter(this);
        painter.drawPixmap((*paintRect), (*pixmap));
        for(int i = 0; i < paintActions.count(); i++)
        {
            paintActions[i]->play(&painter);
        }
    }
}

void Painter::setTool(int id)
{
    unsetCursor();
    switch(id){
    case 1: tool = isPen; break;
    case 2: tool = isLine; break;
    case 3: tool = isRect; break;
    case 4: tool = isEraser;
            setCursor(eraserCursor); break;
    default: tool = tool; break;
    }
}

void Painter::penSettings(int penWidth, Qt::PenCapStyle penCapStyle)
{
    QPen temp(pen->pen());
    temp.setWidth(penWidth);
    temp.setCapStyle(penCapStyle);
    pen->setPen(temp);
}

void Painter::lineSettings(Qt::PenStyle lineStyle,
                           Qt::PenCapStyle lineCapStyle,
                           bool polyLineEnabled, int lineWidth)
{
    isPolylineEnabled = polyLineEnabled;

    QPen temp(pen->pen());
    temp.setWidth(lineWidth);
    temp.setCapStyle(lineCapStyle);
    temp.setStyle(lineStyle);
    line->setPen(temp);
}

void Painter::rectSettings(int drawType, Qt::BrushStyle fillStyle,
                           Qt::PenStyle boundaryStyle,
                           Qt::PenJoinStyle boundaryJoinStyle,
                           bool fillFColor, int boundaryWidth)
{
    type = static_cast<Painter::Type>(drawType);
    fillWithFColor = fillFColor;
    QColor color = (fillWithFColor) ? foregroundColor : backgroundColor;

    QBrush btemp(rect->brush());
    btemp.setColor(color);
    btemp.setStyle(fillStyle);
    rect->setBrush(btemp);

    QPen ptemp(rect->pen());
    ptemp.setStyle(boundaryStyle);
    ptemp.setJoinStyle(boundaryJoinStyle);
    ptemp.setWidth(boundaryWidth);
    rect->setPen(ptemp);
}

void Painter::eraserSettings(int size)
{
    eraserCursor = eraserCursor.scaled(size, size);
    setCursor(eraserCursor);
}
