/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "m_logswid.h"
#include "ui_m_logswid.h"


M_LogsWid::M_LogsWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::M_LogsWid)
{
    ui->setupUi(this);
    QTimer::singleShot(100,this,SLOT(initFunSLot())); //延时初始化
}

M_LogsWid::~M_LogsWid()
{
    delete ui;
}



void M_LogsWid::initFunSLot()
{
    mLogAlarmWid = new M_LogAlarmWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogAlarmWid);

    mLogEnvWid = new M_LogEnvWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogEnvWid);

    mLogModbusCmdWid = new M_LogModbusCmdWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogModbusCmdWid);

    mLogModbusTransWid = new M_LogModbusTransWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogModbusTransWid);

    mLogRealRecordWid = new M_LogLineRecordWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogRealRecordWid);

    mLogThresholdWid = new M_LogLineThresholdWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogThresholdWid);

    mLogOutputWid = new M_LogOutputRecordWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogOutputWid);
}

void M_LogsWid:: updateWidSlot(int id)
{
    LogComWid *wid = nullptr;
    switch (id) {
    case M_Log_Alarm: wid = mLogAlarmWid; break;
    case M_Log_Env: wid = mLogEnvWid; break;
    case M_Log_Modbus: wid = mLogModbusCmdWid; break;
    case M_Log_Trans: wid = mLogModbusTransWid; break;
    case M_Log_Records: wid = mLogRealRecordWid; break;
    case M_Log_Threshold: wid = mLogThresholdWid; break;
    case M_Log_Output: wid = mLogOutputWid; break;
    default:  break;
    }

    if(wid) ui->stackedWid->setCurrentWidget(wid);
}
