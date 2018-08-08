/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mtest_mainwid.h"
#include "ui_mtest_mainwid.h"
#include "m_testenv/mtest_envwid.h"

MTest_MainWid::MTest_MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MTest_MainWid)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
    QTimer::singleShot(600,this,SLOT(initFunSLot()));
}

MTest_MainWid::~MTest_MainWid()
{
    delete ui;
}


QString MTest_MainWid::getName(int mode)
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


void MTest_MainWid::initFunSLot()
{
    MTest_SwWid *swWid = new MTest_SwWid(ui->tabWidget);
    ui->tabWidget->addTab(swWid, tr("输出位开关"));

    for(int i=Mpdu_Rtu_Test_min; i<=Mpdu_Rtu_Test_delay; ++i) {
        MTest_ThresholdOutputWid *wid = new MTest_ThresholdOutputWid(ui->tabWidget);
        wid->initwid(i);
        ui->tabWidget->addTab(wid, getName(i));
    }

    MTest_OutputEleWid *outputEleWid = new MTest_OutputEleWid(ui->tabWidget);
    ui->tabWidget->addTab(outputEleWid, tr("输出位电能清零"));

    MTest_LineWid *lineWid = new MTest_LineWid(ui->tabWidget);
    ui->tabWidget->addTab(lineWid, tr("相阈值设置"));

    MTest_EnvWid *envWid = new MTest_EnvWid(ui->tabWidget);
    ui->tabWidget->addTab(envWid, tr("传感器阈值设置"));
}
