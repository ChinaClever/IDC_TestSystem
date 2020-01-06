/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mpduv1_mainwid.h"
#include "ui_mpduv1_mainwid.h"

MPDUV1_MainWid::MPDUV1_MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MPDUV1_MainWid)
{
    ui->setupUi(this);

    mSnmp = MV1_SnmpTrans::bulid(this);
    mDpThread = MV1_DpThread::bulid(this);
    mRtuThread = MV1_RtuThread::bulid(this);
    mServiceThread = new MV1_ServiceThread(this);

    timer = new QTimer(this);
    timer->start(1*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
    QTimer::singleShot(47,this,SLOT(initFunSLot())); //延时初始化
}

MPDUV1_MainWid::~MPDUV1_MainWid()
{
    delete ui;
}

void MPDUV1_MainWid::initFunSLot()
{
    mtoolBoxWid = new MPDUV1_ToolBoxWid(ui->toolBoxWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), this, SLOT(toolBoxSlot(int)));
    connect(this,SIGNAL(autoTestChange()),mtoolBoxWid,SLOT(autoTestChangeSlot()));

    mStatusWid = new MV1_StatusWid(ui->stackedWid);
    ui->stackedWid->addWidget(mStatusWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mStatusWid, SLOT(simulateSlot(int)));

    mLogsWid = new MV1_LogsWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogsWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mLogsWid, SLOT(updateWidSlot(int)));

    mTestWid = new MV1Test_MainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mTestWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mTestWid, SLOT(updateWidSlot(int)));

    mSetWid = new MV1Set_MainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mSetWid);

}

void MPDUV1_MainWid::toolBoxSlot(int id)
{
    if(id < Test_Function)
    {
        switch (id) {
        case Test_Rtu: mRtuThread->startThread(); break;
        case Test_SNMP: mSnmp->startRun(); break;
        case Test_Stop: mRtuThread->stopThread(); mSnmp->stopRun(); break;
        default: break;
        }
    } else if(id <= Test_Datas_Wid) {
        ui->stackedWid->setCurrentWidget(mTestWid);
        emit autoTestChange();
    } else if(id < Info_Set) {
         ui->stackedWid->setCurrentWidget(mStatusWid);
    } else if(id == Info_Set) {
        ui->stackedWid->setCurrentWidget(mSetWid);
    } else if(id <= Log_Alarm) {
        ui->stackedWid->setCurrentWidget(mLogsWid);
    }
}

void MPDUV1_MainWid::timeoutDone()
{
    sConfigItem *item = MV1_ConfigFile::bulid()->item;
    MV1_DataPackets::bulid()->packets->devNum = item->devNum;

    if(item->testMode != Test_Stop)
    {
        mDpThread->start();
    }
}
