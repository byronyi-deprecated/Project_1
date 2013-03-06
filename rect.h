#ifndef RECT_H
#define RECT_H

#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>

class Rect : public QPainter
{
    Q_OBJECT
public:
    explicit Rect(QObject *parent = 0);
    
signals:
    
public slots:
    void paintByPress(QPicture*, QMouseEvent*);
    void setDrawType(int );
    void setFillStyle(Qt::BrushStyle );
    void setBoundaryStyle(Qt::PenStyle );
    void setBoundaryJoinStyle(Qt::PenJoinStyle );
    void setFillColor(bool foregroundColor);
    void setBoundaryWidth(int );
private:
    QPen *pen;
    QBrush *brush;
    QColor *foregroundColor;
    QColor *backgroundColor;
};

#endif // RECT_H
