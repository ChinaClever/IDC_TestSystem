/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1_logswid.h"
#include "ui_mv1_logswid.h"


MV1_LogsWid::MV1_LogsWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MV1_LogsWid)
{
    ui->setupUi(this);
    QTimer::singleShot(40,this,SLOT(initFunSLot())); //延时初始化
}

MV1_LogsWid::~MV1_LogsWid()
{
    delete ui;
}



void MV1_LogsWid::initFunSLot()
{
    mLogAlarmWid = new MV1_LogAlarmWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogAlarmWid);

    mLogEnvWid = new MV1_LogEnvWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogEnvWid);

    mLogModbusCmdWid = new MV1_LogModbusCmdWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogModbusCmdWid);

    mLogModbusTransWid = new MV1_LogModbusTransWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogModbusTransWid);

    mLogRealRecordWid = new MV1_LogLineRecordWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogRealRecordWid);

    mLogThresholdWid = new MV1_LogLineThresholdWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogThresholdWid);

    mLogOutputWid = new MV1_LogOutputRecordWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogOutputWid);
}

void MV1_LogsWid:: updateWidSlot(int id)
{
    LogComWid *wid = nullptr;
    switch (id) {
    case Log_Alarm: wid = mLogAlarmWid; break;
    case Log_Env: wid = mLogEnvWid; break;
    case Log_Modbus: wid = mLogModbusCmdWid; break;
    case Log_Trans: wid = mLogModbusTransWid; break;
    case Log_Line: wid = mLogRealRecordWid; break;
    case Log_LineThreshold: wid = mLogThresholdWid; break;
    case Log_Output: wid = mLogOutputWid; break;
    default:  break;
    }

    if(wid) ui->stackedWid->setCurrentWidget(wid);
}
