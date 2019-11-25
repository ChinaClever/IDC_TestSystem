/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1set_switemwid.h"
#include "ui_mv1set_switemwid.h"

MV1Set_SwItemWid::MV1Set_SwItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MV1Set_SwItemWid)
{
    ui->setupUi(this);
    com_setBackColour("", this);
    ui->openRadio->setChecked(true);
}

MV1Set_SwItemWid::~MV1Set_SwItemWid()
{
    delete ui;
}


void MV1Set_SwItemWid::init(int id)
{
    ui->checkBox->setText(tr(" %1 输出位").arg(id+1));
}

void MV1Set_SwItemWid::setSelect(bool checked)
{
    ui->checkBox->setChecked(checked);
}

bool MV1Set_SwItemWid::select()
{
    return ui->checkBox->isChecked();
}

void MV1Set_SwItemWid::setOpen(bool checked)
{
    ui->openRadio->setChecked(checked);
}

void MV1Set_SwItemWid::setClose(bool checked)
{
     ui->closeRadio->setChecked(checked);
}

int MV1Set_SwItemWid::status()
{
    int ret = 0;
    if(ui->openRadio->isChecked())
        ret = 1;
    return ret;
}
