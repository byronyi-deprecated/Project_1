#ifndef LINE_H
#define LINE_H

class Line : public PaintTool
{
    Q_OBJECT
public:
    explicit Line(QObject *parent = 0);
    
signals:
    void setLineStyle(Qt::PenStyle );
    void setLineCapStyle(Qt::PenCapStyle );
    
public slots:
    
};

#endif // LINE_H
