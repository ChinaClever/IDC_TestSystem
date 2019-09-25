#include "rset_mainwid.h"
#include "ui_rset_mainwid.h"
#include "r_setsw/rset_swwid.h"
#include "r_setswcycle/rset_swcyclewid.h"
#include "r_setthreshold/rset_thresholditemwid.h"
#include "r_setthreshold/rset_thresholdoutputwid.h"
#include "r_setele/rset_outputelewid.h"
#include "r_setline/rset_linewid.h"
#include "r_setenv/rset_envwid.h"
#include "r_setloop/rset_loopwid.h"
RSet_MainWid::RSet_MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RSet_MainWid)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
    QTimer::singleShot(600,this,SLOT(initFunSLot()));
}

RSet_MainWid::~RSet_MainWid()
{
    delete ui;
}

QString RSet_MainWid::getName(int mode)
{
    QString str = tr("输出位");

    switch (mode) {
    case Rpdu_Rtu_Test_min: str += tr("最小值"); break;
    case Rpdu_Rtu_Test_crMin: str += tr("下限值"); break;
    case Rpdu_Rtu_Test_crMax: str += tr("上限值"); break;
    case Rpdu_Rtu_Test_max: str += tr("最大值"); break;
    default: break;
    }

    return str;
}
void RSet_MainWid::initFunSLot()
{
    RSet_SwCycleWid *swCycleWid = new RSet_SwCycleWid(ui->tabWidget);
    ui->tabWidget->addTab(swCycleWid, tr("输出位开关循环"));

    RSet_SwWid *swWid = new RSet_SwWid(ui->tabWidget);
    ui->tabWidget->addTab(swWid, tr("输出位开关"));

    for(int i=Rpdu_Rtu_Test_min; i<=Rpdu_Rtu_Test_crMax; ++i) {
        RSet_ThresholdOutputWid *wid = new RSet_ThresholdOutputWid(ui->tabWidget);
        wid->initwid(i);
        ui->tabWidget->addTab(wid, getName(i));
    }
    RSet_OutputEleWid *outputEleWid = new RSet_OutputEleWid(ui->tabWidget);
    ui->tabWidget->addTab(outputEleWid, tr("输出位电能清零"));

    RSet_LineWid *lineWid = new RSet_LineWid(ui->tabWidget);
    ui->tabWidget->addTab(lineWid, tr("相阈值设置"));

    RSet_EnvWid *envWid = new RSet_EnvWid(ui->tabWidget);
    ui->tabWidget->addTab(envWid, tr("传感器阈值设置"));

    //RSet_LoopWid *loopWid = new RSet_LoopWid(ui->tabWidget);
    //ui->tabWidget->addTab(loopWid, tr("回路阈值设置"));
}
