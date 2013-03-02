#include "painter.h"

Painter::Painter(QWidget *parent) :
    QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    pixmap = new QPixmap;
    curSize.setHeight(0);
    curSize.setWidth(0);
}

void Painter::init()
{
    setSize();
    update();
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
}

void Painter::setSize()
{
    bool ok;
    int width = QInputDialog::getInt(this, tr("Painter"),
                                         tr("Please enter the width"
                                            "(less than 1024)"),
                                         400, 0, 1024, 1, &ok);
    if(!ok) return;
    int height = QInputDialog::getInteger(this, tr("Painter"),
                                         tr("Please enter the height"
                                            "(less than 1024)"),
                                         300, 0, 1024, 1, &ok);
    if(!ok) return;
    curSize.setWidth(width);
    curSize.setHeight(height);
}
