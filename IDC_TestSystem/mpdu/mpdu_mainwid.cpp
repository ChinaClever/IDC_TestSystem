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
    mRtuThread = new M_RtuThread(this);
    mServiceThread = new M_ServiceThread(this);

    timer = new QTimer(this);
    timer->start(1*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
    QTimer::singleShot(100,this,SLOT(initFunSLot())); //延时初始化
}

MPDU_MainWid::~MPDU_MainWid()
{
    delete ui;
}

void MPDU_MainWid::initFunSLot()
{
    mtoolBoxWid = new MPDU_ToolBoxWid(ui->toolBoxWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), this, SLOT(toolBoxSlot(int)));

    mStatusWid = new M_StatusWid(ui->stackedWid);
    ui->stackedWid->addWidget(mStatusWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mStatusWid, SLOT(simulateSlot(int)));

    mLogsWid = new M_LogsWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogsWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mLogsWid, SLOT(updateWidSlot(int)));

    mTestWid = new MTest_MainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mTestWid);

}

void MPDU_MainWid::toolBoxSlot(int id)
{
    if((id >= Info_Line) && (id < Info_Set)) {
        ui->stackedWid->setCurrentWidget(mStatusWid);
    } else if((id >= Log_Modbus) && (id <= Log_Alarm)) {
        ui->stackedWid->setCurrentWidget(mLogsWid);
    } else if(id == Info_Set) {
        ui->stackedWid->setCurrentWidget(mTestWid);
    } else {
        sConfigItem *item = M_ConfigFile::bulid()->item;
        switch (id) {
        case Test_Rtu: mRtuThread->startThread(); break;
        case Test_SNMP: mSnmp->startRun(item->ip, item->msecs * 100); break;
        case Test_Stop: mRtuThread->stopThread(); mSnmp->stopRun(); break;
        default: break;
        }
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
