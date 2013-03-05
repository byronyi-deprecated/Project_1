#include "pendialog.h"
#include <QtGui>

PenDialog::PenDialog(int &curWidth,
                     Qt::PenCapStyle &curCapStyle,
                     QWidget *parent) :
    QDialog(parent)
{
    yes = new QPushButton(tr("&Yes"), this);
    apply = new QPushButton(tr("&Apply"), this);
    no = new QPushButton(tr("&No"), this);
    no->setDefault(true);
    apply->setDisabled(true);
    connect(this, SIGNAL(capStyleChanged(bool)),
            apply, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(widthChanged(bool)),
            apply, SLOT(setEnabled(bool)));
    connect(apply, SIGNAL(clicked()),
            this, SLOT(applySettings()));

    label = new QLabel(tr("Pen &width"));
    width = new QSlider(Qt::Horizontal, this);
    spinBox = new QSpinBox(this);
    label->setBuddy(width);

    width->setRange(0, 40);
    spinBox->setRange(0, 40);

    connect(spinBox, SIGNAL(valueChanged(int)),
            width, SLOT(setValue(int)));
    connect(width, SIGNAL(valueChanged(int)),
            spinBox, SLOT(setValue(int)));

    spinBox->setValue(curWidth);

    groupBox = new QGroupBox(tr("Cap style"));
    flatCap = new QRadioButton(tr("Flat cap"));
    squareCap = new QRadioButton(tr("Square cap"));
    roundCap = new QRadioButton(tr("Round cap"));

    buttonGroup = new QButtonGroup;
    buttonGroup->addButton(flatCap);
    buttonGroup->addButton(squareCap);
    buttonGroup->addButton(roundCap);
    buttonGroup->setExclusive(true);
    styleToButton(curCapStyle)->setChecked(true);

    vbox = new QVBoxLayout;
    vbox->addWidget(flatCap);
    vbox->addWidget(squareCap);
    vbox->addWidget(roundCap);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);
}

void PenDialog::applySettings(int &curWidth,
                              Qt::PenCapStyle &curCapStyle)
{
    curWidth = spinBox->value();
    curCapStyle = buttonToStyle(buttonGroup->checkedButton());
}

QRadioButton* PenDialog::styleToButton(Qt::PenCapStyle s)
{
    switch(s){
    case Qt::FlatCap:
        return flatCap;
    case Qt::SquareCap:
        return squareCap;
    case Qt::RoundCap:
        return roundCap;
    default: return 0;
    }
}

Qt::PenCapStyle PenDialog::buttonToStyle(QAbstractButton *b)
{
    QRadioButton *temp = dynamic_cast<QRadioButton*>(b);
    if(temp == flatCap)
        return Qt::FlatCap;
    else if (temp == squareCap)
        return Qt::SquareCap;
    else if (temp == roundCap)
        return Qt::RoundCap;
    return Qt::FlatCap;
}
