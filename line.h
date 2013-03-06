#ifndef LINE_H
#define LINE_H

#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>

class Line : public QPainter, public QObject
{
    Q_OBJECT
public:
    explicit Line(QPaintDevice *paintDevice = 0);
    
signals:
    
public slots:
    void setLineStyle(Qt::PenStyle );
    void setLineCapStyle(Qt::PenCapStyle );
    void setLineWidth(int );
    void setForegroundColor(QColor );
private:
    QPen pen;
    QBrush brush;
};

#endif // LINE_H
