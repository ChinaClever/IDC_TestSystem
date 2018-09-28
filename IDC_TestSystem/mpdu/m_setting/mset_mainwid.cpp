/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mset_mainwid.h"
#include "ui_mset_mainwid.h"
#include "m_setenv/mset_envwid.h"
#include "m_setting/m_setswcycle/mset_swcyclewid.h"

MSet_MainWid::MSet_MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MSet_MainWid)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
    QTimer::singleShot(600,this,SLOT(initFunSLot()));
}

MSet_MainWid::~MSet_MainWid()
{
    delete ui;
}


QString MSet_MainWid::getName(int mode)
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


void MSet_MainWid::initFunSLot()
{
    MSet_SwCycleWid *swcycleWid = new MSet_SwCycleWid(ui->tabWidget);
    ui->tabWidget->addTab(swcycleWid, tr("输出位开关循环"));

    MSet_SwWid *swWid = new MSet_SwWid(ui->tabWidget);
    ui->tabWidget->addTab(swWid, tr("输出位开关"));

    for(int i=Mpdu_Rtu_Test_min; i<=Mpdu_Rtu_Test_delay; ++i) {
        MSet_ThresholdOutputWid *wid = new MSet_ThresholdOutputWid(ui->tabWidget);
        wid->initwid(i);
        ui->tabWidget->addTab(wid, getName(i));
    }

    MSet_OutputEleWid *outputEleWid = new MSet_OutputEleWid(ui->tabWidget);
    ui->tabWidget->addTab(outputEleWid, tr("输出位电能清零"));

    MSet_LineWid *lineWid = new MSet_LineWid(ui->tabWidget);
    ui->tabWidget->addTab(lineWid, tr("相阈值设置"));

    MSet_EnvWid *envWid = new MSet_EnvWid(ui->tabWidget);
    ui->tabWidget->addTab(envWid, tr("传感器阈值设置"));
}
