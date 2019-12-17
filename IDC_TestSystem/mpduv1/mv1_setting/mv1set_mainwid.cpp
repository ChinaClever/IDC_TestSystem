/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1set_mainwid.h"
#include "ui_mv1set_mainwid.h"
#include "mv1_setenv/mv1set_envwid.h"
#include "mv1_setting/mv1_setswcycle/mv1set_swcyclewid.h"

MV1Set_MainWid::MV1Set_MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MV1Set_MainWid)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
    QTimer::singleShot(200,this,SLOT(initFunSLot()));
}

MV1Set_MainWid::~MV1Set_MainWid()
{
    delete ui;
}


QString MV1Set_MainWid::getName(int mode)
{
    QString str = tr("输出位");

    switch (mode) {
    case Mpdu_Rtu_Test_min: str += tr("最小值"); break;
    case Mpdu_Rtu_Test_crMin: str += tr("下限值"); break;
    case Mpdu_Rtu_Test_crMax: str += tr("上限值"); break;
    case Mpdu_Rtu_Test_max: str += tr("最大值"); break;
    case Mpdu_Rtu_Test_delay: str += tr("上下电延时"); break;
    default: break;
    }

    return str;
}


void MV1Set_MainWid::initFunSLot()
{
    MV1Set_SwCycleWid *swcycleWid = new MV1Set_SwCycleWid(ui->tabWidget);
    ui->tabWidget->addTab(swcycleWid, tr("输出位开关循环"));

    MV1Set_SwWid *swWid = new MV1Set_SwWid(ui->tabWidget);
    ui->tabWidget->addTab(swWid, tr("输出位开关"));

    for(int i=Mpdu_Rtu_Test_min; i<=Mpdu_Rtu_Test_delay; ++i) {
        MV1Set_ThresholdOutputWid *wid = new MV1Set_ThresholdOutputWid(ui->tabWidget);
        wid->initwid(i);
        ui->tabWidget->addTab(wid, getName(i));
    }

    MV1Set_OutputEleWid *outputEleWid = new MV1Set_OutputEleWid(ui->tabWidget);
    ui->tabWidget->addTab(outputEleWid, tr("输出位电能清零"));

    MV1Set_LineWid *lineWid = new MV1Set_LineWid(ui->tabWidget);
    ui->tabWidget->addTab(lineWid, tr("相阈值设置"));

    MV1Set_EnvWid *envWid = new MV1Set_EnvWid(ui->tabWidget);
    ui->tabWidget->addTab(envWid, tr("传感器阈值设置"));
}
