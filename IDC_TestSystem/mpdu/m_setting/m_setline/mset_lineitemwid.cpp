/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mset_lineitemwid.h"
#include "ui_mset_lineitemwid.h"

MSet_LineItemWid::MSet_LineItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MSet_LineItemWid)
{
    ui->setupUi(this);
}

MSet_LineItemWid::~MSet_LineItemWid()
{
    delete ui;
}


QString MSet_LineItemWid::getTypeName(int type)
{
    QString str;
    switch (type) {
    case Mpdu_Rtu_Test_min: str += tr("最小值"); break;
    case Mpdu_Rtu_Test_max: str += tr("最大值"); break;
    case Mpdu_Rtu_Test_crMin: str += tr("下限值"); break;
    case Mpdu_Rtu_Test_crMax: str += tr("上限值"); break;
    default: break;
    }

    return str;
}

int MSet_LineItemWid::getReg(int mode, int type)
{
//    int reg = 1085;
//    if(mode) reg = 1079;
    int reg = ZM_RtuReg_LineCurMin;
    if(mode) reg = ZM_RtuReg_LineVolMin;

    switch (type) {
    case Mpdu_Rtu_Test_min: /*reg += 0;*/ break;
    case Mpdu_Rtu_Test_max: /*reg += 3;*/ reg += 0x100;break;
    case Mpdu_Rtu_Test_crMin: /*reg = 1205;*/reg += 0x200;break;
    case Mpdu_Rtu_Test_crMax: /*reg = 1208;*/reg += 0x300;break;
    default: break;
    }

    return reg;
}


void MSet_LineItemWid::initwid(int mode, int type)
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2, ui->widget_3};
    for(int i=0; i<3; ++i) {
        mWid[i] = new MSet_ThresholdItemWid(wid[i]);
        mWid[i]->initLine(i, mode);
    }
    mReg  = getReg(mode, type);

    QString str = tr("相电流");
    if(mode) str = tr("相电压");
    str += getTypeName(type);
    ui->label->setText(str);
}
