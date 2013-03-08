#include "linedialog.h"

LineDialog::LineDialog(QWidget *parent) :
    QDialog(parent)
{
    createLineStyle();
    createCapStyle();
    createLineType();

    label = new QLabel(tr("Line width"));
    slider = new QSlider(Qt::Horizontal);
    spinBox = new QSpinBox;
    slider->setRange(1, 10);
    spinBox->setRange(1, 10);

    connect(slider, SIGNAL(valueChanged(int)),
            spinBox, SLOT(setValue(int)));
    connect(spinBox, SIGNAL(valueChanged(int)),
            slider, SLOT(setValue(int)));

    spinBox->setValue(2);

    widthLayout = new QHBoxLayout;
    widthLayout->addWidget(slider);
    widthLayout->addWidget(label);
    widthLayout->addWidget(spinBox);

    yes = new QPushButton(tr("&Yes"));
    no = new QPushButton(tr("&No"));
    connect(yes, SIGNAL(clicked()),
            this, SLOT(applySettings()));
    connect(no, SIGNAL(clicked()),
            this, SLOT(close()));

    yesnoLayout = new QVBoxLayout;
    yesnoLayout->addWidget(yes);
    yesnoLayout->addWidget(no);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(linestyleGroupBox);
    mainLayout->addWidget(capstyleGroupBox);
    mainLayout->addWidget(linetypeGroupBox);
    mainLayout->addLayout(widthLayout);
    mainLayout->addLayout(yesnoLayout);

    setLayout(mainLayout);
    setWindowTitle(tr("Line Settings"));
    setFixedSize(sizeHint());
}

void LineDialog::createLineStyle()
{
    solidline = new QRadioButton(tr("Solid"));
    dash = new QRadioButton(tr("Dash"));
    dot = new QRadioButton(tr("Dot"));
    dado = new QRadioButton(tr("Dash dot"));
    dadodo = new QRadioButton(tr("Dash dot dot"));

    linestyle = new QButtonGroup;
    linestyle->addButton(solidline, 1);
    linestyle->addButton(dash, 2);
    linestyle->addButton(dot, 3);
    linestyle->addButton(dado, 4);
    linestyle->addButton(dadodo, 5);
    linestyle->setExclusive(true);
    solidline->toggle();

    linestyleGroupBox = new QGroupBox(tr("Line style"));
    linestyleLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    linestyleLayout->addWidget(solidline);
    linestyleLayout->addWidget(dash);
    linestyleLayout->addWidget(dot);
    linestyleLayout->addWidget(dado);
    linestyleLayout->addWidget(dadodo);
    linestyleGroupBox->setLayout(linestyleLayout);
}

void LineDialog::createCapStyle()
{
    flat = new QRadioButton(tr("Flat"));
    square = new QRadioButton(tr("Square"));
    round = new QRadioButton(tr("Round"));

    capstyle = new QButtonGroup;
    capstyle->addButton(flat, 0x00);
    capstyle->addButton(square, 0x10);
    capstyle->addButton(round, 0x30);
    round->toggle();

    capstyleGroupBox = new QGroupBox(tr("Cap style"));
    capstyleLayout = new QHBoxLayout;
    capstyleLayout->addWidget(flat);
    capstyleLayout->addWidget(square);
    capstyleLayout->addWidget(round);
    capstyleGroupBox->setLayout(capstyleLayout);
}

void LineDialog::createLineType()
{
    single = new QRadioButton(tr("Single line"));
    poly = new QRadioButton(tr("Polyline"));

    linetype = new QButtonGroup;
    linetype->addButton(single);
    linetype->addButton(poly);
    single->toggle();

    linetypeGroupBox = new QGroupBox(tr("Line type"));
    linetypeLayout = new QVBoxLayout;
    linetypeLayout->addWidget(single);
    linetypeLayout->addWidget(poly);
    linetypeGroupBox->setLayout(linetypeLayout);
}

void LineDialog::applySettings()
{
    emit lineSettings(static_cast<Qt::PenStyle>(linestyle->checkedId()),
                      static_cast<Qt::PenCapStyle>(capstyle->checkedId()),
                      poly->isChecked(), spinBox->value());
    close();
}
