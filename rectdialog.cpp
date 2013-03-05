#include "rectdialog.h"

RectDialog::RectDialog(QWidget *parent) :
    QDialog(parent)
{
    createDrawType();
    createFillStyle();
    createBDStyle();
    createBDJoinStyle();
    createFillColor();

    label = new QLabel(tr("Eraser Size"));
    slider = new QSlider(Qt::Horizontal);
    spinBox = new QSpinBox;
    slider->setRange(1, 40);
    spinBox->setRange(1, 40);
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

    middleLeft->addLayout(BDLayout);
    middleLeft->addLayout(BDJoinLayout);

    middle->addLayout(middleLeft);
    middle->addLayout(colorLayout);

    bottom = new QHBoxLayout;
    bottom->addWidget(slider);
    bottom->addWidget(label);
    bottom->addWidget(spinBox);

    mainLayout->addLayout(drawLayout);
    mainLayout->addLayout(fillLayout);
    mainLayout->addLayout(middle);
    mainLayout->addLayout(bottom);

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

    drawtype = new QButtonGroup(tr("Draw Type"));
    drawtype->addButton(rectangle);
    drawtype->addButton(roundRect);
    drawtype->addButton(circle);
    drawtype->addButton(ellipse);
    drawtype->setExclusive(true);

    drawLayout = new QHBoxLayout;
    drawLayout->addWidget(rectangle);
    drawLayout->addWidget(roundRect);
    drawLayout->addWidget(circle);
    drawLayout->addWidget(ellipse);
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

    fillstyle = new ButtonGroup(tr("Fill Style"));
    fillstyle->addButton(solid);
    fillstyle->addButton(dense1);
    fillstyle->addButton(dense2);
    fillstyle->addButton(dense3);
    fillstyle->addButton(dense4);
    fillstyle->addButton(dense4);
    fillstyle->addButton(dense5);
    fillstyle->addButton(dense6);
    fillstyle->addButton(dense7);
    fillstyle->addButton(horizontal);
    fillstyle->addButton(vertical);
    fillstyle->addButton(cross);
    fillstyle->addButton(bDiag);
    fillstyle->addButton(fDiag);
    fillstyle->addButton(cDiag);
    fillstyle->addButton(nopattern);
    fillstyle->setExclusive(true);

    fillLayout = new QBoxLayout;
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
}

void RectDialog::createBDStyle()
{
    solidline = new QRadioButton(tr("Solid Line"));
    dash = new QRadioButton(tr("Dash Line"));
    dot = new QRadioButton(tr("Dot Line"));
    dado = new QRadioButton(tr("Dash Dot Line"));
    dadodo = new QRadioButton(tr("Dash Dot Dot Line"));
    noline = new QRadioButton(tr("No Line"));

    bdstyle = new QButtonGroup(tr("Boundary Style"));
    fillstyle->addButton(solidline);
    fillstyle->addButton(dash);
    fillstyle->addButton(dot);
    fillstyle->addButton(dado);
    fillstyle->addButton(dadodo);
    fillstyle->addButton(noline);
    fillstyle->setExclusive(true);

    BDLayout = new QBoxLayout;
    BDLayout->addWidget(solidline);
    BDLayout->addWidget(dash);
    BDLayout->addWidget(dot);
    BDLayout->addWidget(dado);
    BDLayout->addWidget(dadodo);
    BDLayout->addWidget(noline);
}

void RectDialog::createBDJoinStyle()
{
    miter = new QRadioButton(tr("Miter Join"));
    bevel = new QRadioButton(tr("Bevel Join"));
    round = new QRadioButton(tr("Round Join"));

    bdjoinstyle = new QButtonGroup(tr("Boundary Join Style"));
    bdjoinstyle->addButton(miter);
    bdjoinstyle->addButton(bevel);
    bdjoinstyle->addButton(round);
    bdjoinstyle->setExclusive(true);

    BDJoinLayout = new QHBoxLayout;
    BDJoinLayout->addWidget(miter);
    BDJoinLayout->addWidget(bevel);
    BDJoinLayout->addWidget(round);
}

void RectDialog::createFillColor()
{
    fground = new QRadioButton(tr("Foreground"));
    bground = new QRadioButton(tr("Background"));

    fillcolor = new QButtonGroup(tr("Fill Color"));
    fillcolor->addButton(fground);
    fillcolor->addButton(bground);
    fillcolor->setExclusive(true);

    colorLayout = new QVBoxLayout;
    colorLayout->addWidget(fground);
    colorLayout->addWidget(bground);
}

void RectDialog::applySettings()
{

}
