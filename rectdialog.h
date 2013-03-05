#ifndef RECTDIALOG_H
#define RECTDIALOG_H

#include <QDialog>
#include <QButtonGroup>
#include <QRadioButton>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>
#include <QLayout>
#include <QPushButton>

class RectDialog : public QDialog
{
    Q_OBJECT
public:
    explicit RectDialog(QWidget *parent = 0);
    
signals:
    void drawType(int );
    void fillStyle(Qt::BrushStyle );
    void boundaryStyle(Qt::PenStyle);
    void boundaryJoinStyle(Qt::PenJoinStyle);
    void fillColor(bool foreground);
    void boundaryWidth(int );
private slots:
    void applySettings();
private:
    void createDrawType();
    void createFillStyle();
    void createBDStyle();
    void createBDJoinStyle();
    void createFillColor();

    QButtonGroup *drawtype;
    QRadioButton *rectangle;
    QRadioButton *roundRect;
    QRadioButton *circle;
    QRadioButton *ellipse;

    QButtonGroup *fillstyle;
    QRadioButton *solid;
    QRadioButton *dense1;
    QRadioButton *dense2;
    QRadioButton *dense3;
    QRadioButton *dense4;
    QRadioButton *dense5;
    QRadioButton *dense6;
    QRadioButton *dense7;
    QRadioButton *horizontal;
    QRadioButton *vertical;
    QRadioButton *cross;
    QRadioButton *bDiag;
    QRadioButton *fDiag;
    QRadioButton *cDiag;
    QRadioButton *nopattern;

    QButtonGroup *bdstyle;
    QRadioButton *solidline;
    QRadioButton *dash;
    QRadioButton *dot;
    QRadioButton *dado;
    QRadioButton *dadodo;
    QRadioButton *noline;

    QButtonGroup *bdjoinstyle;
    QRadioButton *miter;
    QRadioButton *bevel;
    QRadioButton *round;

    QButtonGroup *fillcolor;
    QRadioButton *fground;
    QRadioButton *bground;

    QSlider *slider;
    QLabel *label;
    QSpinBox *spinBox;

    QPushButton *yes;
    QPushButton *no;

    QVBoxLayout *mainLayout;
    QHBoxLayout *drawLayout;
    QBoxLayout *fillLayout;
    QBoxLayout *BDLayout;
    QHBoxLayout *BDJoinLayout;
    QVBoxLayout *colorLayout;

    QVBoxLayout *middleLeft;
    QHBoxLayout *middle;

    QHBoxLayout *bottom;
};

#endif // RECTDIALOG_H
