#include "sitesttoolwid.h"
#include "ui_sitesttoolwid.h"

SiTestToolWid::SiTestToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SiTestToolWid)
{
    ui->setupUi(this);

    QGridLayout *gridLayout = new QGridLayout(parent);//控制toolbox自适应
    gridLayout->addWidget(this);
}

SiTestToolWid::~SiTestToolWid()
{
    delete ui;
}
