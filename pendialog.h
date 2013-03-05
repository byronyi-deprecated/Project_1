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
    PenDialog(int &curWidth,
              Qt::PenCapStyle &curCapStyle,
              QWidget *parent = 0);

signals:
    void capStyleChanged(bool);
    void widthChanged(bool);
    QPen p;
    
private slots:
    void applySettings();

private:
    QRadioButton* styleToButton(Qt::PenCapStyle );
    Qt::PenCapStyle buttonToStyle(QRadioButton *);
    QPushButton *yes;
    QPushButton *apply;
    QPushButton *no;

    QSlider *width;
    QSpinBox *spinBox;
    QLabel *label;

    Qt::PenCapStyle capStyle;
    QGroupBox *groupBox;
    QRadioButton *flatCap;
    QRadioButton *squareCap;
    QRadioButton *roundCap;
    QButtonGroup *buttonGroup;
    QVBoxLayout *vbox;
};

#endif // PENDIALOG_H
