/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "buslogswid.h"
#include "ui_buslogswid.h"
#include "bus_com/bus_configfile.h"

BusLogsWid::BusLogsWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BusLogsWid)
{
    ui->setupUi(this);

    QTimer::singleShot(55,this,SLOT(initFunSLot())); //延时初始化
}

BusLogsWid::~BusLogsWid()
{
    delete ui;
}


void BusLogsWid::initFunSLot()
{
    mLogAlarmWid = new BusLogAlarmWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogAlarmWid);

    mLogEnvWid = new BusLogEnvWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogEnvWid);

    mLogModbusCmdWid = new BusLogModbusCmdWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogModbusCmdWid);

    mLogModbusTransWid = new BusLogModbusTransWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogModbusTransWid);

    mLogRealRecordWid = new BusLogRealRecordWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogRealRecordWid);

    mLogThresholdWid = new BusLogThresholdWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogThresholdWid);
}

void BusLogsWid:: updateWidSlot(int id)
{
    LogComWid *wid = nullptr;
    switch (id) {
    case BUS_Log_Alarm: wid = mLogAlarmWid; break;
    case BUS_Log_Env: wid = mLogEnvWid; break;
    case BUS_Log_Modbus: wid = mLogModbusCmdWid; break;
    case BUS_Log_Trans: wid = mLogModbusTransWid; break;
    case BUS_Log_Records: wid = mLogRealRecordWid; break;
    case BUS_Log_Threshold: wid = mLogThresholdWid; break;
    default:  break;
    }

    if(wid) ui->stackedWid->setCurrentWidget(wid);
}
