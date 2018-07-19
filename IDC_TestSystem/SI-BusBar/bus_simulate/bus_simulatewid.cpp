/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "bus_simulatewid.h"
#include "ui_bus_simulatewid.h"

BUS_SimulateWid::BUS_SimulateWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BUS_SimulateWid)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->start(1*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
    mSimulateThread = new BUS_SimulateThread(this);

    QTimer::singleShot(100,this,SLOT(initFunSLot())); //延时初始化
}

BUS_SimulateWid::~BUS_SimulateWid()
{
    delete ui;
}

void BUS_SimulateWid::timeoutDone()
{
    emit updateSig();
}

void BUS_SimulateWid::initFunSLot()
{
    mBusTableWid = new BUS_BusTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mBusTableWid);
    connect(this, SIGNAL(updateSig()), mBusTableWid, SLOT(updateData()));

    mBoxTableWid = new BUS_BoxTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mBoxTableWid);
    connect(this, SIGNAL(updateSig()), mBoxTableWid, SLOT(updateData()));

    mLoopTableWid = new BUS_LoopTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLoopTableWid);
    connect(this, SIGNAL(updateSig()), mLoopTableWid, SLOT(updateData()));

    mTransTableWid = new BUS_TransTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mTransTableWid);
    connect(this, SIGNAL(updateSig()), mTransTableWid, SLOT(updateData()));

    mThresholdTableWid = new BUS_ThresholdTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mThresholdTableWid);
    connect(this, SIGNAL(updateSig()), mThresholdTableWid, SLOT(updateData()));

    mEnvTableWid = new BUS_EnvTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mEnvTableWid);
    connect(this, SIGNAL(updateSig()), mEnvTableWid, SLOT(updateData()));
}

void BUS_SimulateWid:: simulateSlot(int id)
{
    BUS_LoopTableWid *wid = nullptr;
    switch (id) {
    case BUS_Test_Stop: mSimulateThread->stopThread(); break;
    case BUS_Test_Simulate: mSimulateThread->startThread(); break;
    case BUS_Info_Bus: wid = mBusTableWid; break;
    case BUS_Info_Box: wid = mBoxTableWid; break;
    case BUS_Info_Loop: wid = mLoopTableWid; break;
    case BUS_Info_Trans: wid = mTransTableWid; break;
    case BUS_Info_Threshold: wid = mThresholdTableWid; break;
    case BUS_Info_Env: wid = mEnvTableWid; break;
    default:  break;
    }

    if(wid) ui->stackedWid->setCurrentWidget(wid);
}
