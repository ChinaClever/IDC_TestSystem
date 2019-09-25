/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "r_logswid.h"
#include "ui_r_logswid.h"

R_LogsWid::R_LogsWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::R_LogsWid)
{
    ui->setupUi(this);
    QTimer::singleShot(80,this,SLOT(initFunSLot())); //延时初始化
}

R_LogsWid::~R_LogsWid()
{
    delete ui;
}


void R_LogsWid::initFunSLot()
{
    mLogAlarmWid = new R_LogAlarmWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogAlarmWid);

    mLogEnvWid = new R_LogEnvWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogEnvWid);

    mLogModbusCmdWid = new R_LogModbusCmdWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogModbusCmdWid);

    mLogModbusTransWid = new R_LogModbusTransWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogModbusTransWid);

    mLogRealRecordWid = new R_LogLineRecordWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogRealRecordWid);

    mLogThresholdWid = new R_LogLineThresholdWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogThresholdWid);

    mLogOutputWid = new R_LogOutputRecordWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogOutputWid);

    mLogLoopWid = new R_LogLoopRecordWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogLoopWid);
}

void R_LogsWid:: updateWidSlot(int id)
{
    LogComWid *wid = nullptr;
    switch (id) {
    case Log_Alarm: wid = mLogAlarmWid; break;
    case Log_Env: wid = mLogEnvWid; break;
    case Log_Modbus: wid = mLogModbusCmdWid; break;
    case Log_Trans: wid = mLogModbusTransWid; break;
    case Log_Line: wid = mLogRealRecordWid; break;
    case Log_LineThreshold: wid = mLogThresholdWid; break;
    case Log_Loop: wid = mLogLoopWid; break;
    case Log_Output: wid = mLogOutputWid; break;
    default:  break;
    }

    if(wid) ui->stackedWid->setCurrentWidget(wid);
}
