#include "zset_mainwid.h"
#include "ui_zset_mainwid.h"
#include "z_setsw/zset_swwid.h"
#include "z_setthreshold/zset_thresholditemwid.h"
#include "z_setthreshold/zset_thresholdoutputwid.h"
#include "z_setele/zset_outputelewid.h"
#include "z_setline/zset_linewid.h"
#include "z_setenv/zset_envwid.h"
#include "z_setloop/zset_loopwid.h"
ZSet_MainWid::ZSet_MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZSet_MainWid)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
    QTimer::singleShot(600,this,SLOT(initFunSLot()));
}

ZSet_MainWid::~ZSet_MainWid()
{
    delete ui;
}

QString ZSet_MainWid::getName(int mode)
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
void ZSet_MainWid::initFunSLot()
{
    ZSet_SwWid *swWid = new ZSet_SwWid(ui->tabWidget);
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
