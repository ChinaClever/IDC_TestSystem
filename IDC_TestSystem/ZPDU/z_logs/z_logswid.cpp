/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "z_logswid.h"
#include "ui_z_logswid.h"

Z_LogsWid::Z_LogsWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Z_LogsWid)
{
    ui->setupUi(this);
    QTimer::singleShot(100,this,SLOT(initFunSLot())); //延时初始化
}

Z_LogsWid::~Z_LogsWid()
{
    delete ui;
}


void Z_LogsWid::initFunSLot()
{
    mLogAlarmWid = new Z_LogAlarmWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogAlarmWid);

    mLogEnvWid = new Z_LogEnvWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogEnvWid);

    mLogModbusCmdWid = new Z_LogModbusCmdWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogModbusCmdWid);

    mLogModbusTransWid = new Z_LogModbusTransWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogModbusTransWid);

    mLogRealRecordWid = new Z_LogLineRecordWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogRealRecordWid);

    mLogThresholdWid = new Z_LogLineThresholdWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogThresholdWid);

    mLogOutputWid = new Z_LogOutputRecordWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogOutputWid);

    mLogLoopWid = new Z_LogLoopRecordWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogLoopWid);
}

void Z_LogsWid:: updateWidSlot(int id)
{
    LogComWid *wid = nullptr;
    switch (id) {
    case Z_Log_Alarm: wid = mLogAlarmWid; break;
    case Z_Log_Env: wid = mLogEnvWid; break;
    case Z_Log_Modbus: wid = mLogModbusCmdWid; break;
    case Z_Log_Trans: wid = mLogModbusTransWid; break;
    case Z_Log_Records: wid = mLogRealRecordWid; break;
    case Z_Log_Threshold: wid = mLogThresholdWid; break;
    case Z_Log_Loop: wid = mLogLoopWid; break;
    case Z_Log_Output: wid = mLogOutputWid; break;
    default:  break;
    }

    if(wid) ui->stackedWid->setCurrentWidget(wid);
}
