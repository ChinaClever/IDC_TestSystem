/*
 * Si 主窗口
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "simainwid.h"
#include "ui_simainwid.h"


SIMainWid::SIMainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SIMainWid)
{
    ui->setupUi(this);

    QTimer::singleShot(100,this,SLOT(initFunSLot())); //延时初始化
}

SIMainWid::~SIMainWid()
{
    delete ui;
}

void SIMainWid::initFunSLot()
{
    initWid();
    mServiceThread = new SI_ServiceThread(this);
    mSimulateThread = new SI_SimulateThread(this);
}

void SIMainWid::initWid()
{
    mtoolBoxWid = new SitoolBoxWid(ui->toolBoxWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), this, SLOT(toolBoxSlot(int)));

    mDevTableWid = new SI_DevTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mDevTableWid);

    mTransTableWid = new SI_TransTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mTransTableWid);

    mThresholdTableWid = new SI_ThresholdTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mThresholdTableWid);

    mEnvTableWid = new SI_EnvTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mEnvTableWid);

    mSetMainWid = new SI_SetMainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mSetMainWid);

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

void SIMainWid::toolBoxSlot(int id)
{
    switch (id) {
    case SI_Test_Stop:
        mSimulateThread->stopThread();
        break;

    case SI_Test_Simulate:
        mSimulateThread->startThread();
        break;

    case SI_DevReal_Info:
        ui->stackedWid->setCurrentWidget(mDevTableWid);
        break;

    case SI_Trans_Info:
        ui->stackedWid->setCurrentWidget(mTransTableWid);
        break;

    case SI_Threshold_Info:
        ui->stackedWid->setCurrentWidget(mThresholdTableWid);
        break;

    case SI_Env_Info:
        ui->stackedWid->setCurrentWidget(mEnvTableWid);
        break;

    case SI_DevSet_Info:
        ui->stackedWid->setCurrentWidget(mSetMainWid);
        break;

    case SI_Log_Modbus:
        ui->stackedWid->setCurrentWidget(mLogModbusCmdWid);
        break;

    case SI_Log_Trans:
        ui->stackedWid->setCurrentWidget(mLogModbusTransWid);
        break;

    case SI_Log_Env:
        ui->stackedWid->setCurrentWidget(mLogEnvWid);
        break;

    case SI_Log_Records:
        ui->stackedWid->setCurrentWidget(mLogRealRecordWid);
        break;

    case SI_Log_Threshold:
        ui->stackedWid->setCurrentWidget(mLogThresholdWid);
        break;

    case SI_Log_Alarm:
        ui->stackedWid->setCurrentWidget(mLogAlarmWid);
        break;

    default:
        break;
    }
}
