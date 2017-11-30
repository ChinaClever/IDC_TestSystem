#include "sienvtablewid.h"
#include "ui_sienvtablewid.h"

SiEnvTableWid::SiEnvTableWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SiEnvTableWid)
{
    ui->setupUi(this);
}

SiEnvTableWid::~SiEnvTableWid()
{
    delete ui;
}
