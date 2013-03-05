#ifndef LINEDIALOG_H
#define LINEDIALOG_H

#include <QDialog>
#include <QButtonGroup>
#include <QRadioButton>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>
#include <QLayout>

class LineDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LineDialog(QWidget *parent = 0);

signals:
    void lineStyle(Qt::PenStyle);
    void lineCapStyle(Qt::PenCapStyle);
    void polyLineEnabled(bool);
    void lineWidth(int);
private slots:
    void applySettings();
private:
    QButtonGroup *linestyle;
    QRadioButton *solidline;
    QRadioButton *dash;
    QRadioButton *dot;
    QRadioButton *dado;
    QRadioButton *dadodo;

    QButtonGroup *capstyle;
    QRadioButton *flat;
    QRadioButton *square;
    QRadioButton *round;

    QButtonGroup *linetype;
    QRadioButton *single;
    QRadioButton *poly;

    QSlider *slider;
    QLabel *label;
    QSpinBox *spinBox;

    QPushButton *yes;
    QPushButton *no;
};

#endif // LINEDIALOG_H
