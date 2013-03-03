#ifndef PAINTER_H
#define PAINTER_H

#include <QString>
#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <Qsize>
#include <QInputDialog>
#include <QRect>

class Painter : public QWidget
{
    Q_OBJECT
public:
    Painter(QWidget *parent = 0);
    void init();
    void clear();
    bool readFile(QString fileName);
    bool writeFile(QString fileName);
    QColor curFColor() const {return foregroundColor;}
    QColor curBColor() const {return backgroundColor;}
    QSize curSize() const
        {if(!pixmap) return QSize(0, 0); else return pixmap->size();}
    double curZoomFactor() const {return zoomFactor;}
    void setFColor(QColor curColor) {foregroundColor = curColor;}
    void setBColor(QColor curColor) {backgroundColor = curColor;}
    bool setSize();
    void setZoomFactor(double z);
    bool isNull;
public slots:
    void unDo();
    void reDo();
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
private:


    enum toolState {null, pen, line, eraser, rectangle};
    QRect *rect;
    QPixmap *pixmap;
    QColor foregroundColor;
    QColor backgroundColor;
    double zoomFactor;
};

#endif // PAINTER_H
