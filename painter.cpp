#include "painter.h"

Painter::Painter(QWidget *parent) :
    QWidget(parent)
{
    setBackgroundRole(QPalette::Window);
    isNull = true;
    pixmap = new QPixmap(0, 0);
    pixmap->fill();
    update();
}

void Painter::init()
{
    setSize();
    update();
    isNull = false;
}

void Painter::clear()
{

}

bool Painter::readFile(QString fileName)
{
    if(!fileName.isEmpty())
    {
        pixmap->load(fileName);
        update();
        isNull = false;
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

void Painter::zoomIn()
{

}

void Painter::zoomOut()
{

}

void Painter::mousePressEvent(QMouseEvent *e)
{

}

void Painter::mouseDoubleClickEvent(QMouseEvent *e)
{

}

void Painter::mouseMoveEvent(QMouseEvent *e)
{

}

void Painter::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    if(!pixmap->isNull())
    {
        p.drawPixmap(0, 0, (*pixmap));
    }
}

bool Painter::setSize()
{
    bool ok;
    int width = QInputDialog::getInt(this, tr("Painter"),
                                         tr("Please enter the width"
                                            "(less than 1024)"),
                                     pixmap->width(), 0,
                                     1024, 1, &ok);
    if(!ok) return false;
    int height = QInputDialog::getInt(this, tr("Painter"),
                                         tr("Please enter the height"
                                            "(less than 1024)"),
                                      pixmap->height(), 0,
                                      1024, 1, &ok);
    if(!ok) return false;
    if(width == pixmap->width() &&
            height == pixmap->height())
        return false;
    if(pixmap->isNull())
    {
        *pixmap = QPixmap(1, 1);
        pixmap->fill();
    }
    *pixmap = pixmap->scaled(width, height);
    update();
    return true;
}
