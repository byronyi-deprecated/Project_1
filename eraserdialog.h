#ifndef ERASERDIALOG_H
#define ERASERDIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

class EraserDialog : public QDialog
{
    Q_OBJECT
public:
    explicit EraserDialog(QWidget *parent = 0);
    
signals:
    void eraserSettings(int size);
private slots:
    void applySettings();
private:
    QHBoxLayout *topLayout;
    QHBoxLayout *bottomLayout;
    QVBoxLayout *mainLayout;

    QSlider *slider;
    QSpinBox *spinBox;
    QLabel *label;
    QPushButton *yes;
    QPushButton *no;
};

#endif // ERASERDIALOG_H
