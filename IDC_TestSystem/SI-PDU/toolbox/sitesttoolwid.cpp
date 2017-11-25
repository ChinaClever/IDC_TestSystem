#include "sitesttoolwid.h"
#include "ui_sitesttoolwid.h"

SiTestToolWid::SiTestToolWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SiTestToolWid)
{
    ui->setupUi(this);
}

SiTestToolWid::~SiTestToolWid()
{
    delete ui;
}
