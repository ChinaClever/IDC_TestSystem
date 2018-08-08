/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mtest_switemwid.h"
#include "ui_mtest_switemwid.h"

MTest_SwItemWid::MTest_SwItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MTest_SwItemWid)
{
    ui->setupUi(this);
    com_setBackColour("", this);
    ui->openRadio->setChecked(true);
}

MTest_SwItemWid::~MTest_SwItemWid()
{
    delete ui;
}


void MTest_SwItemWid::init(int id)
{
    ui->checkBox->setText(tr(" %1 输出位").arg(id+1));
}

void MTest_SwItemWid::setSelect(bool checked)
{
    ui->checkBox->setChecked(checked);
}

bool MTest_SwItemWid::select()
{
    return ui->checkBox->isChecked();
}

void MTest_SwItemWid::setOpen(bool checked)
{
    ui->openRadio->setChecked(checked);
}

void MTest_SwItemWid::setClose(bool checked)
{
     ui->closeRadio->setChecked(checked);
}

int MTest_SwItemWid::status()
{
    int ret = 0;
    if(ui->openRadio->isChecked())
        ret = 1;
    return ret;
}
