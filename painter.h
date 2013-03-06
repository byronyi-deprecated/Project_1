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

#include "pen.h"
#include "line.h"
#include "rect.h"
#include "eraser.h"

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
    QSize curSize() const
        {if(!pixmap) return QSize(0, 0); else return pixmap->size();}
    double curZoomFactor() const {return zoomFactor;}
    QColor curBColor() const {return backgroundColor;}
    bool isNull() {return pixmap->isNull();}
public slots:
    void unDo();
    void reDo();
    void setTool(int);
    void setFColor(QColor);
    void setBColor(QColor);
    bool setSize(QSize size);
    void setZoomFactor(double z);

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
    void fColorChanged(QColor );
    void bColorChanged(QColor );
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
    enum Tool {null, isPen, isLine, isRect, isEraser} tool;
    QRect *paintRect;
    QPoint cursorPos;
    QPixmap *pixmap;
    QVector<QPicture> paintActions;
    QVector<QPicture> reDoActions;
    double zoomFactor;

    Pen *pen;
    Line *line;
    Rect *rect;
    Eraser *eraser;
    QColor backgroundColor;
};

#endif // PAINTER_H
