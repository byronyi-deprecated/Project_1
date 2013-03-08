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
    {if(!mainPixmap) return QSize(0, 0); else return mainPixmap.size();}
    double curZoomFactor() const {return zoomFactor;}
    QColor curFColor() const {return foregroundColor;}
    QColor curBColor() const {return backgroundColor;}
    bool isNull() {return mainPixmap.isNull();}
public slots:
    void unDo();
    void reDo();
    void setTool(int);
    void setFColor(QColor);
    void setBColor(QColor);
    bool setSize(QSize size);
    void setZoomFactor(double z);

    void penSettings(int penWidth, Qt::PenCapStyle penCapStyle);

    void lineSettings(Qt::PenStyle lineStyle,
                      Qt::PenCapStyle lineCapStyle,
                      bool polyLineEnabled, int lineWidth);

    void rectSettings(int drawType, Qt::BrushStyle fillStyle,
                      Qt::PenStyle boundaryStyle,
                      Qt::PenJoinStyle boundaryJoinStyle,
                      bool fillFColor, int boundaryWidth);

    void eraserSettings(int eraserSize);
signals:
    void cursorChanged();
    void zoomFactorChanged();
    void imageModified(bool );
    void pensettings();
    void linesettings();
    void rectsettings();
    void erasersettings();
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
private:
    void createPaintDevice();
    void clearUnReDo();
    void setPen(QPainter*);
    void setLine(QPainter*);
    void setRect(QPainter*);
    void setEraser(QPainter*);

    QRect *paintRect;
    QPoint cursorPos;
    QPixmap mainPixmap;
    QPixmap backupPixmap;
    bool undo;
    bool isPainting;
    QPixmap temp;
    QPixmap *eraserCursor;

    QPoint start;
    QPoint end;
    QVector<QPoint > polyline;

//    QVector<QPixmap*> unDoList;
//    QVector<QPixmap*> reDoList;

    enum Tool {null, isPen, isLine, isRect, isEraser} tool;
    double zoomFactor;
    QColor foregroundColor;
    QColor backgroundColor;

    int penWidth;
    Qt::PenCapStyle penCapStyle;

    Qt::PenStyle lineStyle;
    Qt::PenCapStyle lineCapStyle;
    bool polyLineEnabled;
    int lineWidth;

    int drawType;
    Qt::BrushStyle fillStyle;
    Qt::PenStyle boundaryStyle;
    Qt::PenJoinStyle boundaryJoinStyle;
    bool fillFColor;
    int boundaryWidth;

    int eraserSize;
};

#endif // PAINTER_H
