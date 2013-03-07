#ifndef LINEDIALOG_H
#define LINEDIALOG_H

#include <QDialog>
#include <QButtonGroup>
#include <QRadioButton>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>
#include <QLayout>
#include <QPushButton>
#include <QGroupBox>

class LineDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LineDialog(QWidget *parent = 0);

signals:
    void lineSettings(Qt::PenStyle lineStyle,
                      Qt::PenCapStyle lineCapStyle,
                      bool polyLineEnabled, int lineWidth);
private slots:
    void applySettings();
private:
    void createLineStyle();
    void createCapStyle();
    void createLineType();

    QButtonGroup *linestyle;
    QRadioButton *solidline;
    QRadioButton *dash;
    QRadioButton *dot;
    QRadioButton *dado;
    QRadioButton *dadodo;    
    QBoxLayout *linestyleLayout;
    QGroupBox *linestyleGroupBox;

    QButtonGroup *capstyle;
    QRadioButton *flat;
    QRadioButton *square;
    QRadioButton *round;
    QHBoxLayout *capstyleLayout;
    QGroupBox *capstyleGroupBox;

    QButtonGroup *linetype;
    QRadioButton *single;
    QRadioButton *poly;
    QVBoxLayout *linetypeLayout;
    QGroupBox *linetypeGroupBox;

    QSlider *slider;
    QLabel *label;
    QSpinBox *spinBox;
    QHBoxLayout *widthLayout;

    QPushButton *yes;
    QPushButton *no;
    QVBoxLayout *yesnoLayout;

    QVBoxLayout *mainLayout;
};

#endif // LINEDIALOG_H
