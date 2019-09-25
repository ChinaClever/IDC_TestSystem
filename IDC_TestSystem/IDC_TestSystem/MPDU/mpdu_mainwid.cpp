/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mpdu_mainwid.h"
#include "ui_mpdu_mainwid.h"

MPDU_MainWid::MPDU_MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MPDU_MainWid)
{
    ui->setupUi(this);

    mSnmp = M_SnmpTrans::bulid(this);
    mDpThread = M_DpThread::bulid(this);
    mRtuThread = M_RtuThread::bulid(this);
    mServiceThread = new M_ServiceThread(this);

    timer = new QTimer(this);
    timer->start(1*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
    QTimer::singleShot(45,this,SLOT(initFunSLot())); //延时初始化
}

MPDU_MainWid::~MPDU_MainWid()
{
    delete ui;
}

void MPDU_MainWid::initFunSLot()
{
    mtoolBoxWid = new MPDU_ToolBoxWid(ui->toolBoxWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), this, SLOT(toolBoxSlot(int)));
    connect(this,SIGNAL(autoTestChange()),mtoolBoxWid,SLOT(autoTestChangeSlot()));

    mStatusWid = new M_StatusWid(ui->stackedWid);
    ui->stackedWid->addWidget(mStatusWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mStatusWid, SLOT(simulateSlot(int)));

    mLogsWid = new M_LogsWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogsWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mLogsWid, SLOT(updateWidSlot(int)));

    mTestWid = new MTest_MainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mTestWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mTestWid, SLOT(updateWidSlot(int)));

    mSetWid = new MSet_MainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mSetWid);

}

void MPDU_MainWid::toolBoxSlot(int id)
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

void MPDU_MainWid::timeoutDone()
{
    sConfigItem *item = M_ConfigFile::bulid()->item;
    M_DataPackets::bulid()->packets->devNum = item->devNum;

    if(item->testMode != Test_Stop)
    {
        mDpThread->start();
    }
}
