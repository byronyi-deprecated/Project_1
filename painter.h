#ifndef PAINTER_H
#define PAINTER_H

#include <QString>
#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>

class Painter : public QWidget
{
    Q_OBJECT
public:
    Painter(QWidget *parent = 0);
    void clear();
    bool readFile(QString fileName);
    bool writeFile(QString fileName);
    QColor curFColor() const {return foregroundColor;}
    QColor curBColor() const {return backgroundColor;}
    void setFColor(QColor curColor) {foregroundColor = curColor;}
    void setBColor(QColor curColor) {backgroundColor = curColor;}
public slots:
    void zoomIn();
    void zoomOut();
    void unDo();
    void reDo();
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
private:
    enum toolState {null, pen, line, eraser, rectangle};
    QPixmap pixmap;
    QColor foregroundColor;
    QColor backgroundColor;
};

#endif // PAINTER_H
