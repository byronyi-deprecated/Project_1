#include "eraserdialog.h"

EraserDialog::EraserDialog(QWidget *parent) :
    QDialog(parent)
{
    label = new QLabel(tr("Eraser Size"));
    slider = new QSlider(Qt::Horizontal);
    spinBox = new QSpinBox;
    slider->setRange(10, 50);
    spinBox->setRange(10, 50);
    connect(slider, SIGNAL(valueChanged(int)),
            spinBox, SLOT(setValue(int)));
    connect(spinBox, SIGNAL(valueChanged(int)),
            slider, SLOT(setValue(int)));
    spinBox->setValue(20);

    yes = new QPushButton(tr("&Yes"));
    no = new QPushButton(tr("&No"));
    connect(yes, SIGNAL(clicked()),
            this, SLOT(applySettings()));
    connect(no, SIGNAL(clicked()),
            this, SLOT(hide()));

    topLayout = new QHBoxLayout;
    topLayout->addWidget(slider);
    topLayout->addWidget(label);
    topLayout->addWidget(spinBox);

    bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(yes);
    bottomLayout->addWidget(no);

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);

    setLayout(mainLayout);
    setWindowTitle(tr("Eraser settings"));
    setFixedSize(sizeHint());
}

void EraserDialog::applySettings()
{
    emit eraserSettings(spinBox->value());
    hide();
}
