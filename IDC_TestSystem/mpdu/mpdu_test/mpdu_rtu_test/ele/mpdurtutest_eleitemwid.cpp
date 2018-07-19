/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mpdurtutest_eleitemwid.h"
#include "ui_mpdurtutest_eleitemwid.h"

MpduRtuTest_EleItemWid::MpduRtuTest_EleItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MpduRtuTest_EleItemWid)
{
    ui->setupUi(this);
    com_setBackColour("", this);
}

MpduRtuTest_EleItemWid::~MpduRtuTest_EleItemWid()
{
    delete ui;
}


void MpduRtuTest_EleItemWid::init(int id)
{
    ui->checkBox->setText(tr(" %1 输出位").arg(id+1));
}

void MpduRtuTest_EleItemWid::setSelect(bool checked)
{
    ui->checkBox->setChecked(checked);
}

bool MpduRtuTest_EleItemWid::select()
{
    return ui->checkBox->isChecked();
}

void MpduRtuTest_EleItemWid::setClean(bool checked)
{
    ui->cleanRadio->setChecked(checked);
}


int MpduRtuTest_EleItemWid::status()
{
    int ret = 0;
    if(ui->cleanRadio->isChecked())
        ret = 1;
    return ret;
}

void MpduRtuTest_EleItemWid::on_cleanRadio_clicked()
{
     ui->checkBox->setChecked(true);
}
