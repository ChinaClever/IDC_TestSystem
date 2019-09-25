/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mset_switemwid.h"
#include "ui_mset_switemwid.h"

MSet_SwItemWid::MSet_SwItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MSet_SwItemWid)
{
    ui->setupUi(this);
    com_setBackColour("", this);
    ui->openRadio->setChecked(true);
}

MSet_SwItemWid::~MSet_SwItemWid()
{
    delete ui;
}


void MSet_SwItemWid::init(int id)
{
    ui->checkBox->setText(tr(" %1 输出位").arg(id+1));
}

void MSet_SwItemWid::setSelect(bool checked)
{
    ui->checkBox->setChecked(checked);
}

bool MSet_SwItemWid::select()
{
    return ui->checkBox->isChecked();
}

void MSet_SwItemWid::setOpen(bool checked)
{
    ui->openRadio->setChecked(checked);
}

void MSet_SwItemWid::setClose(bool checked)
{
     ui->closeRadio->setChecked(checked);
}

int MSet_SwItemWid::status()
{
    int ret = 0;
    if(ui->openRadio->isChecked())
        ret = 1;
    return ret;
}
