#ifndef PAINTER_H
#define PAINTER_H

#include <QString>
#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QSize>
#include <QInputDialog>
#include <QRect>
#include <QErrorMessage>
#include <QPicture>

#include "pendialog.h"

class Painter : public QWidget
{
    Q_OBJECT
public:
    Painter(QWidget *parent = 0);
    void clear();
    bool readFile(QString fileName);
    bool writeFile(QString fileName);
    int curXPos() const {return cursorPos.x();}
    int curYPos() const {return cursorPos.y();}
    QColor curFColor() const {return brush->color();}
    QColor curBColor() const {return backgroundColor;}
    QSize curSize() const
        {if(!pixmap) return QSize(0, 0); else return pixmap->size();}
    double curZoomFactor() const {return zoomFactor;}
    void setFColor(QColor curColor) {brush->setColor(curColor);}
    void setBColor(QColor curColor) {backgroundColor = curColor;}
    bool setSize(QSize size);
    void setZoomFactor(double z);
    bool isNull() {return pixmap->isNull();}
public slots:
    void unDo();
    void reDo();
    void isPen(bool toggled) {tool = toggled ? pen : tool;}
    void isLine(bool toggled){tool = toggled ? line : tool;}
    void isRect(bool toggled) {tool = toggled? rect : tool;}
    void isEraser(bool toggled) {tool = toggled? eraser : tool;}

    void setPenWidth(int );
    void setPenCapStyle(Qt::PenCapStyle );

    void setLineStyle(Qt::PenStyle );
    void setLineCapStyle(Qt::PenCapStyle );
    void setPolyLineEnabled(bool );
    void setLineWidth(int );

    void setDrawType(int );
    void setFillStyle(Qt::BrushStyle );
    void setBoundaryStyle(Qt::PenStyle );
    void setBoundaryJoinStyle(Qt::PenJoinStyle );
    void setFillColor(bool foregroundColor);
    void setBoundaryWidth(int );

    void setEraserSize(int );
signals:
    void cursorChanged();
    void zoomFactorChanged();
    void imageModified(bool );
    void penSettings();
    void lineSettings();
    void rectSettings();
    void eraserSettings();
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
private:
    void createPaintDevice();
    enum Tool {null, pen, line, rect, eraser} tool;
    QRect *paintRect;
    QPoint cursorPos;
    QPixmap *pixmap;
    QVector<QPicture> paintActions;
    QVector<QPicture> reDoActions;
    QColor backgroundColor;
    double zoomFactor;
    QPainter *painter;
    QPen *p;
    QBrush *brush;
    PenDialog *penDialog;
};

#endif // PAINTER_H
