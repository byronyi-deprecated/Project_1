#ifndef PEN_H
#define PEN_H

#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>

class pen : public QPainter
{
    Q_OBJECT
public:
    explicit pen(QObject *parent = 0);
    
signals:
    
public slots:
    void paintByPress(QPicture*, QMouseEvent*);
    void setPenWidth(int );
    void setPenCapStyle(Qt::PenCapStyle );
private:
    QPen *pen;
    QBrush *brush;
};

#endif // PEN_H
