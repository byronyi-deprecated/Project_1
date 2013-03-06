#include "eraser.h"

Eraser::Eraser(QObject *parent) :
    QPainter(parent)
{
    backgroundColor = Qt::white;
    size = QSize(1,1);
    cursor = QPixmap(size);
    cursor.fill();
}

void Eraser::paintByPress(QPicture* p, QMouseEvent* e)
{
    p = new QPicture;
    begin(p);
    QRect rect(e->x() - size.width() / 2,
               e->y() - size.height() / 2,
               size.width(), size.height());
    drawPixmap(rect, cursor);
    end();
}

void Eraser::setEraserSize(int s)
{
    size = QSize(s, s);
    cursor = QPixmap(size);
    cursor.fill(backgroundColor);
}

void Eraser::setBackgroundColor(QColor c)
{
    backgroundColor = c;
    cursor.fill(backgroundColor);
}
