#include "pendialog.h"
#include <QtGui>

PenDialog::PenDialog(QWidget *parent) :
    QDialog(parent)
{
    label = new QLabel(tr("Width"));
    slider = new QSlider(Qt::Horizontal);
    spinBox = new QSpinBox;

    slider->setRange(10, 40);
    spinBox->setRange(10, 40);

    connect(spinBox, SIGNAL(valueChanged(int)),
            slider, SLOT(setValue(int)));
    connect(slider, SIGNAL(valueChanged(int)),
            spinBox, SLOT(setValue(int)));

    capstyle = new QGroupBox(tr("Cap style"));
    flat = new QRadioButton(tr("Flat cap"));
    square = new QRadioButton(tr("Square cap"));
    round = new QRadioButton(tr("Round cap"));

    buttonGroup = new QButtonGroup;
    buttonGroup->addButton(flat, 1);
    buttonGroup->addButton(square, 2);
    buttonGroup->addButton(round, 3);
    buttonGroup->setExclusive(true);

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
