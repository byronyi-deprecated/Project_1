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
    foregroundColor = Qt::black;
    backgroundColor = Qt::white;
    eraserCursor = new QPixmap;
    eraserCursor->load(":/images/eraserCursor.bmp");
    *eraserCursor = eraserCursor->scaled(QSize(10, 10));
    //    QMessageBox::warning(this,"", QString::number(eraserCursor.width()));
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

//void Painter::clearUnReDo()
//{
//    for(int i = 0; i < unDoList.size(); i++)
//        delete unDoList[i];
//    for(int i = 0; i < reDoList.size(); i++)
//        delete reDoList[i];
//    unDoList.clear();
//    reDoList.clear();
//}

void Painter::clear()
{
    start = QPoint(1024, 1024);
    end = QPoint(1024, 1024);
    backupPixmap = mainPixmap;
    zoomFactor = 1.0;
    paintRect->setSize(mainPixmap.size());
    mainPixmap.fill(backgroundColor);
    //    unDoList.append(pixmap);
    update();
}

bool Painter::readFile(QString fileName)
{
    if(!fileName.isEmpty())
    {
        //        clearUnReDo();
        mainPixmap.load(fileName);
        //        unDoList.append(pixmap);
        zoomFactor = 1.0;
        paintRect->setSize(mainPixmap.size());
        update();
    }
    return !fileName.isEmpty();
}

bool Painter::writeFile(QString fileName)
{
    QPixmap saveImage(mainPixmap);
    return saveImage.save(fileName);
}

void Painter::unDo()
{
    if(!undo) return;
    QPixmap temp(mainPixmap);
    mainPixmap = backupPixmap;
    backupPixmap = temp;
    undo = false;
    //    if(unDoList.isEmpty()) return;
    //    reDoList.append(unDoList.last());
    //    unDoList.pop_back();
}

void Painter::reDo()
{
    QPixmap temp(mainPixmap);
    mainPixmap = backupPixmap;
    backupPixmap = mainPixmap;
    //    if(reDoList.isEmpty()) return;
    //    unDoList.append(reDoList.last());
    //    reDoList.pop_back();
}

bool Painter::setSize(QSize size)
{
    if(size == curSize())
        return false;
    if(mainPixmap.isNull())
    {
        mainPixmap = QPixmap(QSize(1, 1));
        mainPixmap.fill();
        emit imageModified(true);
        undo = false;
    }
    backupPixmap = mainPixmap;
    mainPixmap = mainPixmap.scaled(size);
    paintRect->setSize(size);
    update();
    return true;
}

//to be done

void Painter::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        if(tool == null) return;

        //        if(polyLineEnabled) polyline.append(e->pos());
        //        else
        start = e->pos();
        isPainting = true;
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
        end = e->pos();
        update();
    }
}
//to be done
void Painter::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        end = e->pos();
        qDebug() << end.x() << "," << end.y() << endl;
        isPainting = false;
        update();
    }
}

void Painter::mouseDoubleClickEvent(QMouseEvent *e)
{
    if(e->buttons() == Qt::LeftButton && polyLineEnabled)
    {
        if(tool == null) return;
        end = e->pos();
        update();
        polyline.clear();
    }
}

void Painter::paintEvent(QPaintEvent * /* e */)
{
    if(!mainPixmap) return;
    QPainter painter;
    undo = true;

    if(tool == isPen || tool == isEraser){
        painter.begin(&mainPixmap);
        if(tool == isPen){
            setPen(&painter);
            painter.drawLine(start, end);
            start = end;
        }
        else{
            setEraser(&painter);
            painter.drawLine(start, end);
            start = end;
        }
    }
    else
    {
        QRect r(start, end);
        if(isPainting){
            temp = mainPixmap;
            painter.begin(&temp);
        }
        else {
            backupPixmap = mainPixmap;
            painter.begin(&mainPixmap);
        }
        if(tool == isLine){
            setLine(&painter);
            painter.drawLine(start, end);
        }
        else{
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
            default:
                painter.drawRect(r);
            }
        }
    }
    painter.end();
    QPainter p(this);
    if(tool == isPen || tool == isEraser)
        p.drawPixmap((*paintRect), mainPixmap);
    else if(isPainting)
        p.drawPixmap((*paintRect), temp);
    else
        p.drawPixmap((*paintRect), mainPixmap);

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
