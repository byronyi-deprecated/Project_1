#ifndef PEN_H
#define PEN_H

#include <QObject>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>

class Pen : public QObject, public QPainter
{
    Q_OBJECT
public:
    explicit Pen(QPaintDevice *paintDevice = 0);
    
signals:
    
public slots:
    void paintByPress(QPoint);
    void setPenWidth(int );
    void setPenCapStyle(Qt::PenCapStyle );
    void setForegroundColor(QColor );
private:
    QPen pen;
    QBrush brush;
};

#endif // PEN_H
