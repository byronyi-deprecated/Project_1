#ifndef ERASER_H
#define ERASER_H

class Eraser : public PaintTool
{
    Q_OBJECT
public:
    explicit Eraser(QObject *parent = 0);
    
signals:
    void setEraserSize(int );
    
public slots:
    
};

#endif // ERASER_H
