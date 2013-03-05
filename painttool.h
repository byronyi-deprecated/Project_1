#ifndef PAINTTOOL_H
#define PAINTTOOL_H

#include <QPainter>
#include <QPicture>
#include <QMouseEvent>

class PaintTool : public QPainter
{
    Q_OBJECT
public:
    explicit PaintTool(QObject *parent = 0);
    virtual void paintByPress(QPicture*, QMouseEvent *e) = 0;
signals:
    
public slots:
    
};

#endif // PAINTTOOL_H
