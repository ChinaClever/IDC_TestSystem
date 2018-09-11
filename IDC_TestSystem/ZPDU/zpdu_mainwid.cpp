/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "zpdu_mainwid.h"
#include "ui_zpdu_mainwid.h"
#include "z_snmp/z_snmptrans.h"

ZPDU_MainWid::ZPDU_MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZPDU_MainWid)
{
    ui->setupUi(this);
    QTimer::singleShot(100,this,SLOT(initFunSLot())); //延时初始化

    Z_SnmpTrans *snmp = new Z_SnmpTrans(this);
    snmp->startRun("192.168.1.163");

}

ZPDU_MainWid::~ZPDU_MainWid()
{
    delete ui;
}


void ZPDU_MainWid::initFunSLot()
{
    mtoolBoxWid = new Z_ToolBoxWid(ui->toolBoxWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), this, SLOT(toolBoxSlot(int)));

    mStatusWid = new Z_StatusWid(ui->stackedWid);
    ui->stackedWid->addWidget(mStatusWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mStatusWid, SLOT(simulateSlot(int)));

    mLogsWid = new Z_LogsWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogsWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mLogsWid, SLOT(updateWidSlot(int)));

    mTestWid = new ZTest_MainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mTestWid);

    mDpThread = new Z_DpThread(this);
    mRtuThread = new Z_RtuThread(this);
    mServiceThread = new Z_ServiceThread(this);
}

void ZPDU_MainWid::toolBoxSlot(int id)
{
    if((id >= Info_Line) && (id < Info_Set)) {
        ui->stackedWid->setCurrentWidget(mStatusWid);
    } else if((id >= Log_Modbus) && (id <= Log_Alarm)) {
         ui->stackedWid->setCurrentWidget(mLogsWid);
    } else if(id == Info_Set) {
        ui->stackedWid->setCurrentWidget(mTestWid);
    }

    switch (id) {
    case Test_Rtu: mRtuThread->startThread(); break;
    case Test_Stop: mRtuThread->stopThread(); break;

    default: break;
    }

}
