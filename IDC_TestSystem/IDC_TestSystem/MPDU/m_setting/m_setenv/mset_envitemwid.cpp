/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mset_envitemwid.h"
#include "ui_mset_envitemwid.h"

MSet_EnvItemWid::MSet_EnvItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MSet_EnvItemWid)
{
    ui->setupUi(this);
}

MSet_EnvItemWid::~MSet_EnvItemWid()
{
    delete ui;
}


QString MSet_EnvItemWid::getTypeName(int type)
{
    QString str;
    switch (type) {
    case Mpdu_Rtu_Test_min: str += tr("最小值"); break;
    case Mpdu_Rtu_Test_max: str += tr("最大值"); break;
    default: break;
    }

    return str;
}

int MSet_EnvItemWid::getReg(int mode, int type)
{
//    int reg = 1091;
//    if(mode) reg = 1095;
    int reg = ZM_RtuReg_TemMin;
    if(mode) reg = ZM_RtuReg_HumMin;

    switch (type) {
    case Mpdu_Rtu_Test_min: /*reg += 0;*/break;
    case Mpdu_Rtu_Test_max: /*reg += 2;*/reg += 0x100; break;
    default: break;
    }

    return reg;
}


void MSet_EnvItemWid::initwid(int mode, int type)
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2};
    for(int i=0; i<2; ++i) {
        mWid[i] = new MSet_ThresholdItemWid(wid[i]);
        mWid[i]->initEnv(i, mode);
    }
    mReg  = getReg(mode, type);

    QString str = tr("温度");
    if(mode) str = tr("湿度");
    str += getTypeName(type);
    ui->label->setText(str);
}
