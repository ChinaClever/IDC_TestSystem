/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "silogswid.h"
#include "ui_silogswid.h"
#include "si_com/sidatapackets.h"

SILogsWid::SILogsWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SILogsWid)
{
    ui->setupUi(this);
    QTimer::singleShot(100,this,SLOT(initFunSLot())); //延时初始化
}

SILogsWid::~SILogsWid()
{
    delete ui;
}


void SILogsWid::initFunSLot()
{
    mLogModbusCmdWid = new SiLogModbusCmdWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogModbusCmdWid);

    mLogModbusTransWid = new SiLogModbusTransWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogModbusTransWid);

    mLogEnvWid = new SiLogEnvWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogEnvWid);

    mLogRealRecordWid = new SiLogRealRecordWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogRealRecordWid);

    mLogThresholdWid = new SiLogThresholdWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogThresholdWid);

    mLogAlarmWid = new SiLogAlarmWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogAlarmWid);
}

void SILogsWid:: updateWidSlot(int id)
{
    LogComWid *wid = nullptr;
    switch (id) {
    case SI_Log_Alarm: wid = mLogAlarmWid; break;
    case SI_Log_Env: wid = mLogEnvWid; break;
    case SI_Log_Modbus: wid = mLogModbusCmdWid; break;
    case SI_Log_Trans: wid = mLogModbusTransWid; break;
    case SI_Log_Records: wid = mLogRealRecordWid; break;
    case SI_Log_Threshold: wid = mLogThresholdWid; break;
    default:  break;
    }

    if(wid) ui->stackedWid->setCurrentWidget(wid);
}
