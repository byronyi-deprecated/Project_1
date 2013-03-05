#include "eraserdialog.h"

EraserDialog::EraserDialog(QWidget *parent) :
    QDialog(parent)
{
    label = new QLabel(tr("Eraser Size"));
    slider = new QSlider(Qt::Horizontal);
    spinBox = new QSpinBox;
    slider->setRange(1, 10);
    spinBox->setRange(1, 10);
    connect(slider, SIGNAL(valueChanged(int)),
            spinBox, SLOT(setValue(int)));
    connect(spinBox, SIGNAL(valueChanged(int)),
            slider, SLOT(setValue(int)));

    yes = new QPushButton(tr("&Yes"));
    no = new QPushButton(tr("&No"));
    connect(yes, SIGNAL(clicked()),
            this, SLOT(applySettings()));
    connect(no, SIGNAL(clicked()),
            this, SLOT(close()));

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
    emit eraserSize(spinBox->value());
    close();
}
