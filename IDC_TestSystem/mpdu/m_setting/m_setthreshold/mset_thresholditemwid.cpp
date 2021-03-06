﻿/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mset_thresholditemwid.h"
#include "ui_mset_thresholditemwid.h"

MSet_ThresholdItemWid::MSet_ThresholdItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MSet_ThresholdItemWid)
{
    ui->setupUi(this);    
    com_setBackColour("", this);
    mRate = 1;
}

MSet_ThresholdItemWid::~MSet_ThresholdItemWid()
{
    delete ui;
}


QString MSet_ThresholdItemWid::getStr(int mode)
{
    QString str=tr("电流");

    switch (mode) {
    case Mpdu_Rtu_Test_min: str += tr("最小值"); break;
    case Mpdu_Rtu_Test_max: str += tr("最大值"); break;
    case Mpdu_Rtu_Test_crMin: str += tr("下限值"); break;
    case Mpdu_Rtu_Test_crMax: str += tr("上限值"); break;
    case Mpdu_Rtu_Test_delay: str = tr("上下电延时");
        ui->spinBox->setSuffix("S");
        break;
    default: break;
    }

    return str;
}

void MSet_ThresholdItemWid::initOutput(int id, int mode)
{
    QString str =getStr(mode);
    ui->checkBox->setText(tr(" %1 输出位%2").arg(id+1).arg(str));
}

void MSet_ThresholdItemWid::initLine(int id, int mode)
{
    ui->checkBox->setText(tr(" L%1").arg(id+1));
    if(mode) ui->spinBox->setSuffix("V");
}

void MSet_ThresholdItemWid::initEnv(int id, int mode)
{
    QString name, str;
    if(mode) {
        name = tr("湿度");
        str = "%";
    } else {
        name = tr("温度");
        str = "℃";
    }

    ui->checkBox->setText(tr(" %1%2").arg(name).arg(id+1));
    ui->spinBox->setSuffix(str);
}

void MSet_ThresholdItemWid::setSelect(bool checked)
{
    ui->checkBox->setChecked(checked);
}

bool MSet_ThresholdItemWid::select()
{
    return ui->checkBox->isChecked();
}

void MSet_ThresholdItemWid::setValue(int value)
{
    ui->spinBox->setValue(value);
}


int MSet_ThresholdItemWid::status()
{
    int ret = -1;
    if(ui->checkBox->isChecked())
        ret = ui->spinBox->value()*mRate;

    return ret;
}

void MSet_ThresholdItemWid::on_spinBox_valueChanged(int arg1)
{
    ui->checkBox->setChecked(true);
}
