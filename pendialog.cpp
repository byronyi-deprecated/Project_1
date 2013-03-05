#include "pendialog.h"
#include <QtGui>

PenDialog::PenDialog(QWidget *parent) :
    QDialog(parent)
{
    label = new QLabel(tr("Pen &width"));
    slider = new QSlider(Qt::Horizontal, this);
    spinBox = new QSpinBox(this);
    label->setBuddy(slider);

    slider->setRange(0, 40);
    spinBox->setRange(0, 40);

    connect(spinBox, SIGNAL(valueChanged(int)),
            slider, SLOT(setValue(int)));
    connect(slider, SIGNAL(valueChanged(int)),
            spinBox, SLOT(setValue(int)));

    groupBox = new QGroupBox(tr("Cap style"));
    flatCap = new QRadioButton(tr("Flat cap"));
    squareCap = new QRadioButton(tr("Square cap"));
    roundCap = new QRadioButton(tr("Round cap"));

    buttonGroup = new QButtonGroup;
    buttonGroup->addButton(flatCap, 1);
    buttonGroup->addButton(squareCap, 2);
    buttonGroup->addButton(roundCap, 3);
    buttonGroup->setExclusive(true);

    yes = new QPushButton(tr("&Yes"), this);
    no = new QPushButton(tr("&No"), this);
    no->setDefault(true);
    connect(yes, SIGNAL(clicked()),
            this, SLOT(applySettings()));
    connect(no, SIGNAL(clicked()),
            this, SLOT(close()));

    topLeftLayout = new QVBoxLayout;
    topLeftLayout->addWidget(flatCap);
    topLeftLayout->addWidget(squareCap);
    topLeftLayout->addWidget(roundCap);
    topLeftLayout->addStretch(1);
    groupBox->setLayout(topLeftLayout);

    topLayout = new QHBoxLayout;
    topLayout->addLayout(topLeftLayout);
    topLayout->addWidget(yes);
    topLayout->addWidget(no);

    bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(slider);
    bottomLayout->addWidget(label);
    bottomLayout->addWidget(spinBox);

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);

    this->setLayout(mainLayout);
}

void PenDialog::applySettings()
{
    emit penWidth(spinBox->value());
    emit penCapStyle(buttonToStyle());
    this->close();
}

QRadioButton* PenDialog::styleToButton(Qt::PenCapStyle s)
{
    switch(s){
    case Qt::FlatCap:
        return flatCap;
    case Qt::SquareCap:
        return squareCap;
    default: return roundCap;
    }
}

Qt::PenCapStyle PenDialog::buttonToStyle()
{
  switch(buttonGroup->checkedId()){
    case 1: return Qt::FlatCap;
    case 2: return Qt::SquareCap;
    default: return Qt::RoundCap;
    }
}
