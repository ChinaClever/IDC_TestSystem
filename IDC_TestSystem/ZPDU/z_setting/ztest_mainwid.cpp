#include "ztest_mainwid.h"
#include "ui_ztest_mainwid.h"
#include "z_testsw/ztest_swwid.h"
#include "z_testthreshold/ztest_thresholditemwid.h"
#include "z_testthreshold/ztest_thresholdoutputwid.h"
#include "z_setele/zset_outputelewid.h"
#include "z_setline/zset_linewid.h"
#include "z_setenv/zset_envwid.h"
#include "z_setloop/zset_loopwid.h"
ZTest_MainWid::ZTest_MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZTest_MainWid)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
    QTimer::singleShot(600,this,SLOT(initFunSLot()));
}

ZTest_MainWid::~ZTest_MainWid()
{
    delete ui;
}

QString ZTest_MainWid::getName(int mode)
{
    QString str = tr("输出位");

    switch (mode) {
    case Zpdu_Rtu_Test_min: str += tr("最小值"); break;
    case Zpdu_Rtu_Test_crMin: str += tr("下限值"); break;
    case Zpdu_Rtu_Test_crMax: str += tr("上限值"); break;
    case Zpdu_Rtu_Test_max: str += tr("最大值"); break;
    default: break;
    }

    return str;
}
void ZTest_MainWid::initFunSLot()
{
    ZTest_SwWid *swWid = new ZTest_SwWid(ui->tabWidget);
    ui->tabWidget->addTab(swWid, tr("输出位开关"));

    for(int i=Zpdu_Rtu_Test_min; i<=Zpdu_Rtu_Test_crMax; ++i) {
        ZTest_ThresholdOutputWid *wid = new ZTest_ThresholdOutputWid(ui->tabWidget);
        wid->initwid(i);
        ui->tabWidget->addTab(wid, getName(i));
    }
    ZSet_OutputEleWid *outputEleWid = new ZSet_OutputEleWid(ui->tabWidget);
    ui->tabWidget->addTab(outputEleWid, tr("输出位电能清零"));

    ZSet_LineWid *lineWid = new ZSet_LineWid(ui->tabWidget);
    ui->tabWidget->addTab(lineWid, tr("相阈值设置"));

    ZSet_EnvWid *envWid = new ZSet_EnvWid(ui->tabWidget);
    ui->tabWidget->addTab(envWid, tr("传感器阈值设置"));

    ZSet_LoopWid *loopWid = new ZSet_LoopWid(ui->tabWidget);
    ui->tabWidget->addTab(loopWid, tr("回路阈值设置"));
}
