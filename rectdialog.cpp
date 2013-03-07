#include "rectdialog.h"

RectDialog::RectDialog(QWidget *parent) :
    QDialog(parent)
{
    createDrawType();
    createFillStyle();
    createBDStyle();
    createBDJoinStyle();
    createFillColor();

    label = new QLabel(tr("Line width"));
    slider = new QSlider(Qt::Horizontal);
    spinBox = new QSpinBox;
    slider->setRange(1, 15);
    spinBox->setRange(1, 15);
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

    bottom = new QHBoxLayout;
    bottom->addWidget(slider);
    bottom->addWidget(label);
    bottom->addWidget(spinBox);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(drawtypeGroupBox);
    mainLayout->addWidget(fillstyleGroupBox);
    mainLayout->addWidget(bdstyleGroupBox);
    mainLayout->addWidget(bdjoinGroupBox);
    mainLayout->addLayout(bottom);
    mainLayout->addWidget(yes);
    mainLayout->addWidget(no);

    setLayout(mainLayout);
    setWindowTitle(tr("Rectangle Settings"));
    setFixedSize(sizeHint());
}

void RectDialog::createDrawType()
{
    rectangle = new QRadioButton(tr("Rectangle"));
    roundRect = new QRadioButton(tr("Round Rectangle"));
    circle = new QRadioButton(tr("Circle"));
    ellipse = new QRadioButton(tr("Ellipse"));

    drawtype = new QButtonGroup;
    drawtype->addButton(rectangle, 0);
    drawtype->addButton(roundRect, 1);
    drawtype->addButton(circle, 2);
    drawtype->addButton(ellipse, 3);
    drawtype->setExclusive(true);

    drawLayout = new QHBoxLayout;
    drawLayout->addWidget(rectangle);
    drawLayout->addWidget(roundRect);
    drawLayout->addWidget(circle);
    drawLayout->addWidget(ellipse);

    drawtypeGroupBox = new QGroupBox(tr("Draw Type"));
    drawtypeGroupBox->setLayout(drawLayout);
}

void RectDialog::createFillStyle()
{
    solid = new QRadioButton(tr("Solid"));
    dense1 = new QRadioButton(tr("Dense 1"));
    dense2 = new QRadioButton(tr("Dense 2"));
    dense3 = new QRadioButton(tr("Dense 3"));
    dense4 = new QRadioButton(tr("Dense 4"));
    dense5 = new QRadioButton(tr("Dense 5"));
    dense6 = new QRadioButton(tr("Dense 6"));
    dense7 = new QRadioButton(tr("Dense 7"));
    horizontal = new QRadioButton(tr("Horizontal"));
    vertical = new QRadioButton(tr("Vertical"));
    cross = new QRadioButton(tr("Cross"));
    bDiag = new QRadioButton(tr("B. Diag"));
    fDiag = new QRadioButton(tr("F. Diag"));
    cDiag = new QRadioButton(tr("C. Diag"));
    nopattern = new QRadioButton(tr("No Pattern"));

    fillstyle = new QButtonGroup;
    fillstyle->addButton(solid, 1);
    fillstyle->addButton(dense1, 2);
    fillstyle->addButton(dense2, 3);
    fillstyle->addButton(dense3, 4);
    fillstyle->addButton(dense4, 5);
    fillstyle->addButton(dense4, 6);
    fillstyle->addButton(dense5, 7);
    fillstyle->addButton(dense6, 8);
    fillstyle->addButton(dense7, 8);
    fillstyle->addButton(horizontal, 9);
    fillstyle->addButton(vertical, 10);
    fillstyle->addButton(cross, 11);
    fillstyle->addButton(bDiag, 12);
    fillstyle->addButton(fDiag, 13);
    fillstyle->addButton(cDiag, 14);
    fillstyle->addButton(nopattern, 0);
    fillstyle->setExclusive(true);

    fillLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    fillLayout->addWidget(solid);
    fillLayout->addWidget(dense1);
    fillLayout->addWidget(dense2);
    fillLayout->addWidget(dense3);
    fillLayout->addWidget(dense4);
    fillLayout->addWidget(dense5);
    fillLayout->addWidget(dense6);
    fillLayout->addWidget(dense7);
    fillLayout->addWidget(horizontal);
    fillLayout->addWidget(vertical);
    fillLayout->addWidget(cross);
    fillLayout->addWidget(bDiag);
    fillLayout->addWidget(fDiag);
    fillLayout->addWidget(cDiag);
    fillLayout->addWidget(nopattern);

    fillstyleGroupBox = new QGroupBox(tr("Fill Style"));
    fillstyleGroupBox->setLayout(fillLayout);
}

void RectDialog::createBDStyle()
{
    solidline = new QRadioButton(tr("Solid Line"));
    dash = new QRadioButton(tr("Dash Line"));
    dot = new QRadioButton(tr("Dot Line"));
    dado = new QRadioButton(tr("Dash Dot Line"));
    dadodo = new QRadioButton(tr("Dash Dot Dot Line"));
    noline = new QRadioButton(tr("No Line"));

    bdstyle = new QButtonGroup;
    bdstyle->addButton(solidline, 1);
    bdstyle->addButton(dash, 2);
    bdstyle->addButton(dot, 3);
    bdstyle->addButton(dado, 4);
    bdstyle->addButton(dadodo, 5);
    bdstyle->addButton(noline, 0);
    bdstyle->setExclusive(true);

    bdLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    bdLayout->addWidget(solidline);
    bdLayout->addWidget(dash);
    bdLayout->addWidget(dot);
    bdLayout->addWidget(dado);
    bdLayout->addWidget(dadodo);
    bdLayout->addWidget(noline);

    bdstyleGroupBox = new QGroupBox(tr("Boundary Style"));
    bdstyleGroupBox->setLayout(bdLayout);
}

void RectDialog::createBDJoinStyle()
{
    miter = new QRadioButton(tr("Miter Join"));
    bevel = new QRadioButton(tr("Bevel Join"));
    round = new QRadioButton(tr("Round Join"));

    bdjoinstyle = new QButtonGroup;
    bdjoinstyle->addButton(miter, 0x00);
    bdjoinstyle->addButton(bevel, 0x40);
    bdjoinstyle->addButton(round, 0x80);
    bdjoinstyle->setExclusive(true);

    bdjoinLayout = new QHBoxLayout;
    bdjoinLayout->addWidget(miter);
    bdjoinLayout->addWidget(bevel);
    bdjoinLayout->addWidget(round);

    bdjoinGroupBox = new QGroupBox(tr("Boundary Join Style"));
    bdjoinGroupBox->setLayout(bdjoinLayout);
}

void RectDialog::createFillColor()
{
    fground = new QRadioButton(tr("Foreground"));
    bground = new QRadioButton(tr("Background"));

    fillcolor = new QButtonGroup;
    fillcolor->addButton(fground, 1);
    fillcolor->addButton(bground, 1);
    fillcolor->setExclusive(true);

    colorLayout = new QVBoxLayout;
    colorLayout->addWidget(fground);
    colorLayout->addWidget(bground);

    colorGroupBox = new QGroupBox(tr("Fill Color"));
    colorGroupBox->setLayout(colorLayout);
}

void RectDialog::applySettings()
{
    emit rectSettings(drawtype->checkedId(),
                      static_cast<Qt::BrushStyle>(fillstyle->checkedId()),
                      static_cast<Qt::PenStyle>(bdstyle->checkedId()),
                      static_cast<Qt::PenJoinStyle>(bdjoinstyle->checkedId()),
                      fground->isChecked(), spinBox->value());
    close();
}
