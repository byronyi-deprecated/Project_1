#ifndef RECT_H
#define RECT_H

#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>

class Rect : public QObject, public QPainter
{
    Q_OBJECT
public:
    explicit Rect(QPaintDevice *paintDevice = 0);
    
signals:
    
public slots:
    void paintByPress(QPoint start, QPoint end);
    void setDrawType(int );
    void setFillStyle(Qt::BrushStyle );
    void setBoundaryStyle(Qt::PenStyle );
    void setBoundaryJoinStyle(Qt::PenJoinStyle );
    void setFillColor(bool foregroundColor);
    void setBoundaryWidth(int );
    void setForegroundColor(QColor f) {pen.setColor(foregroundColor = f);}
    void setBackgroundColor(QColor b) {backgroundColor = b;}

private:
    QPen pen;
    QBrush brush;
    QColor foregroundColor;
    QColor backgroundColor;
    int drawType;
};

#endif // RECT_H
