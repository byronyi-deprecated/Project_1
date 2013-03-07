#ifndef PENDIALOG_H
#define PENDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QButtonGroup>
#include <QGroupBox>
#include <QRadioButton>
#include <QVBoxLayout>

class PenDialog : public QDialog
{
    Q_OBJECT
public:
    PenDialog(QWidget *parent = 0);
signals:
    void penWidth(int);
    void penCapStyle(Qt::PenCapStyle);
private slots:
    void applySettings();
private:
    QRadioButton* styleToButton(Qt::PenCapStyle );
    Qt::PenCapStyle buttonToStyle();

    QGroupBox *capstyle;
    QRadioButton *flat;
    QRadioButton *square;
    QRadioButton *round;
    QButtonGroup *buttonGroup;
    QVBoxLayout *topLeftLayout;

    QPushButton *yes;
    QPushButton *no;
    QVBoxLayout *topRightLayout;

    QHBoxLayout *topLayout;

    QSlider *slider;
    QSpinBox *spinBox;
    QLabel *label;
    QHBoxLayout *bottomLayout;

    QVBoxLayout *mainLayout;
};

#endif // PENDIALOG_H
