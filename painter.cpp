#include "painter.h"
#include <QMessageBox>
#include <QDebug>

Painter::Painter(QWidget *parent) :
    QWidget(parent)
{
    setBackgroundRole(QPalette::Window);
    tool = null;
    createPaintDevice();
    this->setMouseTracking(true);
    emit imageModified(false);
    isPainting = false;
    undo = true;
    foregroundColor = Qt::black;
    backgroundColor = Qt::white;
    eraserCursor = new QPixmap;
    eraserCursor->load(":/images/eraserCursor.bmp");
    *eraserCursor = eraserCursor->scaled(QSize(10, 10));
}

void Painter::createPaintDevice()
{
    start = QPoint(1024, 1024);
    end = QPoint(1024, 1024);
    paintRect = new QRect(this->pos(), QSize(0, 0));
    penSettings(2,Qt::RoundCap);

    lineSettings(Qt::SolidLine,Qt::RoundCap,
                 false,2);

    rectSettings(1,Qt::NoBrush,Qt::SolidLine,
                 Qt::MiterJoin,true,2);

    eraserSettings(5);
}

void Painter::clear()
{
    start = QPoint(1024, 1024);
    end = QPoint(1024, 1024);
    backupPixmap = mainPixmap;
    zoomFactor = 1.0;
    paintRect->setSize(mainPixmap.size());
    mainPixmap.fill(backgroundColor);
    temp = mainPixmap;
    update();
}

bool Painter::readFile(QString fileName)
{
    if(!fileName.isEmpty())
    {
        mainPixmap.load(fileName);
        backupPixmap = mainPixmap;
        zoomFactor = 1.0;
        paintRect->setSize(mainPixmap.size());
        temp = mainPixmap;
        update();
    }
    return !fileName.isEmpty();
}

bool Painter::writeFile(QString fileName)
{
    QPixmap saveImage(mainPixmap);
    return saveImage.save(fileName);
}

void Painter::swap()
{
    QPixmap temp(mainPixmap);
    mainPixmap = backupPixmap;
    backupPixmap = temp;
}

void Painter::unDo()
{
    if(!undo) return;
    swap();
    undo = false;
    temp = mainPixmap;
    update();
}

void Painter::reDo()
{
    if(undo) return;
    swap();
    undo = true;
    temp = mainPixmap;
    update();
}

bool Painter::setSize(QSize size)
{
    if(size == curSize())
        return false;
    if(mainPixmap.isNull())
    {
        mainPixmap = QPixmap(QSize(1, 1));
        mainPixmap.fill();
        temp = mainPixmap;
        emit imageModified(true);
        undo = false;
    }
    backupPixmap = mainPixmap;
    mainPixmap = mainPixmap.scaled(size);
    paintRect->setSize(size);
    undo = true;
    temp = mainPixmap;
    update();
    return true;
}

void Painter::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        if(tool == null) return;
        if(tool == isLine && polyLineEnabled)
            polyline.append(e->pos());
        else
            start = e->pos();
        isPainting = true;
        backupPixmap = mainPixmap;
        undo = true;
        if(tool == isPen || tool == isEraser)
            temp = mainPixmap;
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
    if(tool == isLine && polyLineEnabled && isPainting)
    {
        polyline.last() = e->pos();
        update();
    }
    else if(e->buttons() & Qt::LeftButton)
    {
        end = e->pos();
        update();
    }
}
//to be done
void Painter::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        if(tool == null) return;
        if(tool == isLine && polyLineEnabled && isPainting)
            polyline.append(e->pos());
        else{
            isPainting = false;
            end = e->pos();
        }
        update();
    }
}

void Painter::mouseDoubleClickEvent(QMouseEvent *e)
{
    if(e->buttons() == Qt::LeftButton &&
            tool == isLine && polyLineEnabled)
    {
        isPainting = false;
        update();
        polyline.clear();
    }
}

void Painter::paintEvent(QPaintEvent * /* e */)
{
    QPainter painter;
    if(isPainting)
    {
        if(tool == isRect || tool == isLine)
            temp = mainPixmap;
        painter.begin(&temp);
        QRect r(start * (1/zoomFactor),
                end * (1/zoomFactor));
        switch(tool){
        case isPen:
            setPen(&painter);
            painter.drawLine(start * (1/zoomFactor),
                             end * (1/zoomFactor));
            start = end;
            break;
        case isEraser:
            setEraser(&painter);
            painter.drawLine(start * (1/zoomFactor),
                             end * (1/zoomFactor));
            start = end;
            break;
        case isLine:
            setLine(&painter);
            if(polyLineEnabled && !polyline.empty())
                for(int i = 0; i < polyline.size() - 1; i++)
                    painter.drawLine(polyline[i] * (1/zoomFactor),
                                     polyline[i+1] * (1/zoomFactor));
            else
                painter.drawLine(start * (1/zoomFactor),
                                 end * (1/zoomFactor));
            break;
        case isRect:
            setRect(&painter);
            r = r.normalized();
            switch(drawType){
            case 1:
                painter.drawRect(r);
                break;
            case 2:
                painter.drawRoundedRect(r, 20, 20,
                                        Qt::RelativeSize);
                break;
            case 3:
                painter.drawPie(r, 0, 5760);
                break;
            case 4:
                painter.drawEllipse(r);
                break;
            }
            break;
        default: break;
        }
        painter.end();
        QPainter p(this);
        p.drawPixmap((*paintRect), temp);
    }
    else
    {
        mainPixmap = temp;
        QPainter p(this);
        p.drawPixmap((*paintRect), mainPixmap);
    }
}

void Painter::setZoomFactor(double z)
{
    if(z < 0) zoomFactor = 0.001; else zoomFactor = z;
    emit zoomFactorChanged();
    paintRect->setSize(mainPixmap.size() * zoomFactor);
    update();
}

void Painter::setTool(int id)
{    
    start = QPoint(1024, 1024);
    end = QPoint(1024, 1024);
    unsetCursor();
    switch(id){
    case 1: tool = isPen; break;
    case 2: tool = isLine; break;
    case 3: tool = isRect; break;
    case 4: tool = isEraser;
        setCursor(*eraserCursor); break;
    default: tool = tool; break;
        update();
    }
}

void Painter::setPen(QPainter *p)
{
    QPen temp;
    temp.setColor(foregroundColor);
    temp.setWidth(penWidth);
    temp.setCapStyle(penCapStyle);
    p->setPen(temp);
}

void Painter::setLine(QPainter *p)
{
    QPen temp;
    temp.setColor(foregroundColor);
    temp.setWidth(lineWidth);
    temp.setCapStyle(lineCapStyle);
    temp.setStyle(lineStyle);
    p->setPen(temp);
}

void Painter::setRect(QPainter *p)
{
    QBrush btemp;
    btemp.setColor((fillFColor) ? foregroundColor
                                : backgroundColor);
    btemp.setStyle(fillStyle);
    p->setBrush(btemp);

    QPen ptemp;
    ptemp.setColor(foregroundColor);
    ptemp.setStyle(boundaryStyle);
    ptemp.setJoinStyle(boundaryJoinStyle);
    ptemp.setWidth(boundaryWidth);
    p->setPen(ptemp);
}

void Painter::setEraser(QPainter *p)
{
    *eraserCursor = eraserCursor->scaled(eraserSize, eraserSize);
    setCursor(*eraserCursor);
    QPen temp(QBrush(backgroundColor),eraserSize);
    temp.setCapStyle(Qt::SquareCap);
    p->setPen(temp);
}

void Painter::setFColor(QColor curColor)
{
    foregroundColor = curColor;
}
void Painter::setBColor(QColor curColor)
{
    backgroundColor = curColor;
}

void Painter::penSettings(int w,
                          Qt::PenCapStyle c)
{
    penWidth = w;
    penCapStyle = c;
}


void Painter::lineSettings(Qt::PenStyle l,
                           Qt::PenCapStyle c,
                           bool p, int w)
{
    lineStyle = l;
    lineCapStyle = c;
    polyLineEnabled = p;
    lineWidth = w;
}


void Painter::rectSettings(int d, Qt::BrushStyle f,
                           Qt::PenStyle b,
                           Qt::PenJoinStyle bj,
                           bool c, int w)
{
    drawType = d;
    fillStyle = f;
    boundaryStyle = b;
    boundaryJoinStyle = bj;
    fillFColor = c;
    boundaryWidth = w;
}
void Painter::eraserSettings(int s)
{
    eraserSize = s;
}
