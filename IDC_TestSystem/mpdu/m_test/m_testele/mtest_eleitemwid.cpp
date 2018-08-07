/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mtest_eleitemwid.h"
#include "ui_mtest_eleitemwid.h"

MTest_EleItemWid::MTest_EleItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MTest_EleItemWid)
{
    ui->setupUi(this);
    com_setBackColour("", this);
}

MTest_EleItemWid::~MTest_EleItemWid()
{
    delete ui;
}


void MTest_EleItemWid::init(int id)
{
    ui->checkBox->setText(tr(" %1 输出位").arg(id+1));
}

void MTest_EleItemWid::setSelect(bool checked)
{
    ui->checkBox->setChecked(checked);
}

bool MTest_EleItemWid::select()
{
    return ui->checkBox->isChecked();
}

void MTest_EleItemWid::setClean(bool checked)
{
    ui->cleanRadio->setChecked(checked);
}


int MTest_EleItemWid::status()
{
    int ret = 0;
    if(ui->cleanRadio->isChecked())
        ret = 1;
    return ret;
}

void MTest_EleItemWid::on_cleanRadio_clicked()
{
     ui->checkBox->setChecked(true);
}
