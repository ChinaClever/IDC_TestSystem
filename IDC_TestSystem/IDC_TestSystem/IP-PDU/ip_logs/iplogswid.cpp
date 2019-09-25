/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "iplogswid.h"
#include "ui_iplogswid.h"
#include "ip_com/ipdatapackets.h"

IpLogsWid::IpLogsWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IpLogsWid)
{
    ui->setupUi(this);
    QTimer::singleShot(100,this,SLOT(initFunSLot())); //延时初始化
}

IpLogsWid::~IpLogsWid()
{
    delete ui;
}


void IpLogsWid::initFunSLot()
{
    mLogAlarmWid = new IpLogAlarmWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogAlarmWid);

    mLogEnvWid = new IpLogEnvWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogEnvWid);

    mLogModbusCmdWid = new IpLogModbusCmdWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogModbusCmdWid);

    mLogModbusTransWid = new IpLogModbusTransWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogModbusTransWid);

    mLogRealRecordWid = new IpLogRealRecordWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogRealRecordWid);

    mLogThresholdWid = new IpLogThresholdWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogThresholdWid);
}

void IpLogsWid:: updateWidSlot(int id)
{
    LogComWid *wid = nullptr;
    switch (id) {
    case Log_Alarm: wid = mLogAlarmWid; break;
    case Log_Env: wid = mLogEnvWid; break;
    case Log_Modbus: wid = mLogModbusCmdWid; break;
    case Log_Trans: wid = mLogModbusTransWid; break;
    case Log_Line: wid = mLogRealRecordWid; break;
    case Log_LineThreshold: wid = mLogThresholdWid; break;
    default:  break;
    }

    if(wid) ui->stackedWid->setCurrentWidget(wid);
}
