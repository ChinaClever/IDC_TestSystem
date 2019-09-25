#include "eload_logswid.h"
#include "ui_eload_logswid.h"
#include "eload_com/in_datapackets.h"

ELoad_LogsWid::ELoad_LogsWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ELoad_LogsWid)
{
    ui->setupUi(this);
    QTimer::singleShot(100,this,SLOT(initFunSLot())); //延时初始化
}

ELoad_LogsWid::~ELoad_LogsWid()
{
    delete ui;
}


void ELoad_LogsWid::initFunSLot()
{
    mLogAlarmWid = new ELoad_LogAlarmWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogAlarmWid);

    mLogEnvWid = new ELoad_LogEnvWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogEnvWid);

    mLogModbusCmdWid = new ELoad_LogModbusCmdWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogModbusCmdWid);

    mLogModbusTransWid = new ELoad_LogModbusTransWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogModbusTransWid);

    mLogRealRecordWid = new ELoad_LogLineRecordWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogRealRecordWid);

    mLogThresholdWid = new ELoad_LogLineThresholdWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogThresholdWid);
}

void ELoad_LogsWid:: updateWidSlot(int id)
{
    LogComWid *wid = nullptr;
    switch (id) {
    case ELoad_Log_Alarm: wid = mLogAlarmWid; break;
    case ELoad_Log_Env: wid = mLogEnvWid; break;
    case ELoad_Log_Modbus: wid = mLogModbusCmdWid; break;
    case ELoad_Log_Trans: wid = mLogModbusTransWid; break;
    case ELoad_Log_Output: wid = mLogRealRecordWid; break;
    case ELoad_Log_Threshold: wid = mLogThresholdWid; break;
    default:  break;
    }

    if(wid) ui->stackedWid->setCurrentWidget(wid);
}
