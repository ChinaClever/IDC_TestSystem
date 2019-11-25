/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1set_eleitemwid.h"
#include "ui_mv1set_eleitemwid.h"

MV1Set_EleItemWid::MV1Set_EleItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MV1Set_EleItemWid)
{
    ui->setupUi(this);
    com_setBackColour("", this);
}

MV1Set_EleItemWid::~MV1Set_EleItemWid()
{
    delete ui;
}


void MV1Set_EleItemWid::init(int id)
{
    ui->checkBox->setText(tr(" %1 输出位").arg(id+1));
}

void MV1Set_EleItemWid::setSelect(bool checked)
{
    ui->checkBox->setChecked(checked);
}

bool MV1Set_EleItemWid::select()
{
    return ui->checkBox->isChecked();
}

void MV1Set_EleItemWid::setClean(bool checked)
{
    ui->cleanRadio->setChecked(checked);
}


int MV1Set_EleItemWid::status()
{
    int ret = 0;
    if(ui->cleanRadio->isChecked())
        ret = 1;
    return ret;
}

void MV1Set_EleItemWid::on_cleanRadio_clicked()
{
     ui->checkBox->setChecked(true);
}
