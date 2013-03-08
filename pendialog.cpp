#include "pendialog.h"
#include <QtGui>

PenDialog::PenDialog(QWidget *parent) :
    QDialog(parent)
{
    label = new QLabel(tr("Width"));
    slider = new QSlider(Qt::Horizontal);
    spinBox = new QSpinBox;

    slider->setRange(1, 10);
    spinBox->setRange(1, 10);

    connect(spinBox, SIGNAL(valueChanged(int)),
            slider, SLOT(setValue(int)));
    connect(slider, SIGNAL(valueChanged(int)),
            spinBox, SLOT(setValue(int)));

    spinBox->setValue(2);

    capstyle = new QGroupBox(tr("Cap style"));
    flat = new QRadioButton(tr("Flat cap"));
    square = new QRadioButton(tr("Square cap"));
    round = new QRadioButton(tr("Round cap"));

    buttonGroup = new QButtonGroup;
    buttonGroup->addButton(flat, 0x00);
    buttonGroup->addButton(square, 0x10);
    buttonGroup->addButton(round, 0x20);
    buttonGroup->setExclusive(true);
    round->toggle();

    yes = new QPushButton(tr("&Yes"));
    no = new QPushButton(tr("&No"));
    no->setDefault(true);
    connect(yes, SIGNAL(clicked()),
            this, SLOT(applySettings()));
    connect(no, SIGNAL(clicked()),
            this, SLOT(close()));

    topLeftLayout = new QVBoxLayout;
    topLeftLayout->addWidget(flat);
    topLeftLayout->addWidget(square);
    topLeftLayout->addWidget(round);
    topLeftLayout->addStretch(1);
    capstyle->setLayout(topLeftLayout);

    topRightLayout = new QVBoxLayout;
    topRightLayout->addWidget(yes);
    topRightLayout->addWidget(no);

    topLayout = new QHBoxLayout;
    topLayout->addWidget(capstyle);
    topLayout->addLayout(topRightLayout);

    bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(slider);
    bottomLayout->addWidget(label);
    bottomLayout->addWidget(spinBox);

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);

    setLayout(mainLayout);
    setWindowTitle(tr("Pen Settings"));
    setFixedSize(sizeHint());
}

void PenDialog::applySettings()
{
    emit penSettings(spinBox->value(), static_cast<Qt::PenCapStyle>(buttonGroup->checkedId()));
    close();
}
