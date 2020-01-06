﻿/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "rpdu_mainwid.h"
#include "ui_rpdu_mainwid.h"


RPDU_MainWid::RPDU_MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RPDU_MainWid)
{
    ui->setupUi(this);

    mSnmp = R_SnmpTrans::bulid(this);
    mDpThread = R_DpThread::bulid(this);
    mRtuThread = R_RtuThread::bulid(this);
    mServiceThread = new R_ServiceThread(this);

    timer = new QTimer(this);
    timer->start(1*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
    QTimer::singleShot(57,this,SLOT(initFunSLot())); //延时初始化
}

RPDU_MainWid::~RPDU_MainWid()
{
    delete ui;
}


void RPDU_MainWid::initFunSLot()
{
    mtoolBoxWid = new R_ToolBoxWid(ui->toolBoxWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), this, SLOT(toolBoxSlot(int)));
    connect(this,SIGNAL(autoTestChange()),mtoolBoxWid,SLOT(autoTestChangeSlot()));

    mStatusWid = new R_StatusWid(ui->stackedWid);
    ui->stackedWid->addWidget(mStatusWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mStatusWid, SLOT(simulateSlot(int)));

    mLogsWid = new R_LogsWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogsWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mLogsWid, SLOT(updateWidSlot(int)));

    mTestWid = new RTest_MainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mTestWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mTestWid, SLOT(updateWidSlot(int)));

    mSetWid = new RSet_MainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mSetWid);
}

void RPDU_MainWid::toolBoxSlot(int id)
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

void RPDU_MainWid::timeoutDone()
{
    sConfigItem *item = R_ConfigFile::bulid()->item;
    R_DataPackets::bulid()->packets->devNum = item->devNum;

    if(item->testMode != Test_Stop)
    {
        mDpThread->start();
    }
}
