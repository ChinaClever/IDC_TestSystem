/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mset_eleitemwid.h"
#include "ui_mset_eleitemwid.h"

MSet_EleItemWid::MSet_EleItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MSet_EleItemWid)
{
    ui->setupUi(this);
    com_setBackColour("", this);
}

MSet_EleItemWid::~MSet_EleItemWid()
{
    delete ui;
}


void MSet_EleItemWid::init(int id)
{
    ui->checkBox->setText(tr(" %1 输出位").arg(id+1));
}

void MSet_EleItemWid::setSelect(bool checked)
{
    ui->checkBox->setChecked(checked);
}

bool MSet_EleItemWid::select()
{
    return ui->checkBox->isChecked();
}

void MSet_EleItemWid::setClean(bool checked)
{
    ui->cleanRadio->setChecked(checked);
}


int MSet_EleItemWid::status()
{
    int ret = 0;
    if(ui->cleanRadio->isChecked())
        ret = 1;
    return ret;
}

void MSet_EleItemWid::on_cleanRadio_clicked()
{
     ui->checkBox->setChecked(true);
}
