/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mpdurtutest_switemwid.h"
#include "ui_mpdurtutest_switemwid.h"
extern void com_setBackColour(const QString &,QWidget *target);


MpduRtuTest_SwItemWid::MpduRtuTest_SwItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MpduRtuTest_SwItemWid)
{
    ui->setupUi(this);
    com_setBackColour("", this);
    ui->openRadio->setChecked(true);
}

MpduRtuTest_SwItemWid::~MpduRtuTest_SwItemWid()
{
    delete ui;
}

void MpduRtuTest_SwItemWid::init(int id)
{
    ui->checkBox->setText(tr(" %1 输出位").arg(id+1));
}

void MpduRtuTest_SwItemWid::setSelect(bool checked)
{
    ui->checkBox->setChecked(checked);
}

bool MpduRtuTest_SwItemWid::select()
{
    return ui->checkBox->isChecked();
}

void MpduRtuTest_SwItemWid::setOpen(bool checked)
{
    ui->openRadio->setChecked(checked);
}

void MpduRtuTest_SwItemWid::setClose(bool checked)
{
     ui->closeRadio->setChecked(checked);
}

int MpduRtuTest_SwItemWid::status()
{
    int ret = 0;
    if(ui->openRadio->isChecked())
        ret = 1;
    return ret;
}
