/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mtest_lineitemwid.h"
#include "ui_mtest_lineitemwid.h"

MTest_LineItemWid::MTest_LineItemWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MTest_LineItemWid)
{
    ui->setupUi(this);
}

MTest_LineItemWid::~MTest_LineItemWid()
{
    delete ui;
}


QString MTest_LineItemWid::getTypeName(int type)
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

int MTest_LineItemWid::getReg(int mode, int type)
{
    int reg = 1085;
    if(mode) reg = 1079;

    switch (type) {
    case Mpdu_Rtu_Test_min: reg += 0; break;
    case Mpdu_Rtu_Test_max: reg += 3; break;
    case Mpdu_Rtu_Test_crMin: reg = 1205; break;
    case Mpdu_Rtu_Test_crMax: reg = 1208; break;
    default: break;
    }

    return reg;
}


void MTest_LineItemWid::initwid(int mode, int type)
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2, ui->widget_3};
    for(int i=0; i<3; ++i) {
        mWid[i] = new MTest_ThresholdItemWid(wid[i]);
        mWid[i]->initLine(i, mode);
    }
    mReg  = getReg(mode, type);

    QString str = tr("相电流");
    if(mode) str = tr("相电压");
    str += getTypeName(type);
    ui->label->setText(str);
}
