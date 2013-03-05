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
    vbox->addWidget(buttonGroup);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);
}

void PenDialog::applySettings()
{
    if(!curWidth = spinBox->value())
        emit widthChanged();
    curWidth = spinBox->value();

    switch(buttonGroup->checkedButton()){
    case flatCap:
        curCapStyle = Qt::FlatCap;
        break;
    case squareCap:
        curCapStyle = Qt::SquareCap;
        break;
    case roundCap:
        curCapStyle = Qt::RoundCap;
        break;
    default: break;
    }
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
    default: break;
    }
}

Qt::PenCapStyle PenDialog::buttonToStyle(QRadioButton *b)
{
    switch(b){
    case flatCap:
        return Qt::FlatCap;
    case squareCap:
        return Qt::SquareCap;
    case roundCap:
        return Qt::RoundCap;
    default: break;
    }
}
