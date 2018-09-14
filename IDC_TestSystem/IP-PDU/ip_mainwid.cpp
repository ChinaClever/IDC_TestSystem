/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ip_mainwid.h"
#include "ui_ip_mainwid.h"

IP_MainWid::IP_MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IP_MainWid)
{
    ui->setupUi(this);

    mSnmp = new IP_SnmpTrans(this);
    mDpThread = IP_DpThread::bulid(this);
    mRtuThread = new IP_RtuThread(this);
    mServiceThread = new IP_ServiceThread(this);

    timer = new QTimer(this);
    timer->start(1*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
    QTimer::singleShot(10,this,SLOT(initFunSLot())); //延时初始化
}

IP_MainWid::~IP_MainWid()
{
    delete ui;
}

void IP_MainWid::initFunSLot()
{
    mtoolBoxWid = new IP_ToolBoxWid(ui->toolBoxWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), this, SLOT(toolBoxSlot(int)));

    mStatusWid = new IP_StatusWid(ui->stackedWid);
    ui->stackedWid->addWidget(mStatusWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mStatusWid, SLOT(simulateSlot(int)));

    mLogsWid = new IpLogsWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogsWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mLogsWid, SLOT(updateWidSlot(int)));
}

void IP_MainWid::toolBoxSlot(int id)
{
    if((id >= Info_Line) && (id <= Info_Set)) {
        ui->stackedWid->setCurrentWidget(mStatusWid);
    } else if((id >= Log_Modbus) && (id <= Log_Alarm)) {
         ui->stackedWid->setCurrentWidget(mLogsWid);
    } else {
        sConfigItem *item = IP_ConfigFile::bulid()->item;
        switch (id) {
        case Test_Rtu: mRtuThread->startThread(); break;
        case Test_SNMP: mSnmp->startRun(item->ip, item->msecs * 100); break;
        case Test_Stop: mRtuThread->stopThread(); mSnmp->stopRun(); break;
        default: break;
        }
    }
}

void IP_MainWid::timeoutDone()
{
    sConfigItem *item = IP_ConfigFile::bulid()->item;
    IpDataPackets::bulid()->packets->devNum = item->devNum;
    if(item->testMode != Test_Stop)
    {
        mDpThread->start();
    }
}
