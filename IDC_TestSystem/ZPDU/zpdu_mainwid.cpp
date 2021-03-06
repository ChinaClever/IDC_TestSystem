﻿/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "zpdu_mainwid.h"
#include "ui_zpdu_mainwid.h"


ZPDU_MainWid::ZPDU_MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZPDU_MainWid)
{
    ui->setupUi(this);

    mSnmp = Z_SnmpTrans::bulid(this);
    mDpThread = Z_DpThread::bulid(this);
    mRtuThread = Z_RtuThread::bulid(this);
    mServiceThread = new Z_ServiceThread(this);

    timer = new QTimer(this);
    timer->start(1*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
    QTimer::singleShot(60,this,SLOT(initFunSLot())); //延时初始化
}

ZPDU_MainWid::~ZPDU_MainWid()
{
    delete ui;
}


void ZPDU_MainWid::initFunSLot()
{
    mtoolBoxWid = new Z_ToolBoxWid(ui->toolBoxWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), this, SLOT(toolBoxSlot(int)));
    connect(this,SIGNAL(autoTestChange()),mtoolBoxWid,SLOT(autoTestChangeSlot()));

    mStatusWid = new Z_StatusWid(ui->stackedWid);
    ui->stackedWid->addWidget(mStatusWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mStatusWid, SLOT(simulateSlot(int)));

    mLogsWid = new Z_LogsWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogsWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mLogsWid, SLOT(updateWidSlot(int)));

    mTestWid = new ZTest_MainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mTestWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mTestWid, SLOT(updateWidSlot(int)));

    mSetWid = new ZSet_MainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mSetWid);
}

void ZPDU_MainWid::toolBoxSlot(int id)
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

void ZPDU_MainWid::timeoutDone()
{
    sConfigItem *item = Z_ConfigFile::bulid()->item;
    Z_DataPackets::bulid()->packets->devNum = item->devNum;

    if(item->testMode != Test_Stop)
    {
        mDpThread->start();
    }
}
