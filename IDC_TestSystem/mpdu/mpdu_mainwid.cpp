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

    mSimulateWid = new M_SimulateWid(ui->stackedWid);
    ui->stackedWid->addWidget(mSimulateWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mSimulateWid, SLOT(simulateSlot(int)));

    mLogsWid = new M_LogsWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogsWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mLogsWid, SLOT(updateWidSlot(int)));

    mTestWid = new MpduRtuTest_MainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mTestWid);

//    mServiceThread = new IP_ServiceThread(this);
}

void MPDU_MainWid::toolBoxSlot(int id)
{
    if((id >= M_Info_Dev) && (id <= M_Info_Set)) {
        ui->stackedWid->setCurrentWidget(mSimulateWid);
    } else if((id >= M_Log_Modbus) && (id <= M_Log_Alarm)) {
         ui->stackedWid->setCurrentWidget(mLogsWid);
    }
}
