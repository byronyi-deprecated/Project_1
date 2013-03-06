#ifndef LINE_H
#define LINE_H

#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>

class Line : public QPainter
{
    Q_OBJECT
public:
    explicit Line(QObject *parent = 0);
    
signals:
    
public slots:
    void paintByPress(QPicture*, QMouseEvent*);
    void setLineStyle(Qt::PenStyle );
    void setLineCapStyle(Qt::PenCapStyle );
    void setPolyLineEnabled(bool );
    void setLineWidth(int );
private:
    QPen *pen;
    QBrush *brush;
};

#endif // LINE_H
