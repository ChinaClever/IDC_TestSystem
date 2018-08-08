/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "si_simulatewid.h"
#include "ui_si_simulatewid.h"

SI_SimulateWid::SI_SimulateWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SI_SimulateWid)
{
    ui->setupUi(this);
    mSimulateThread = new SI_SimulateThread(this);

    QTimer::singleShot(100,this,SLOT(initFunSLot())); //延时初始化
}

SI_SimulateWid::~SI_SimulateWid()
{
    delete ui;
}


void SI_SimulateWid::initFunSLot()
{
    sDevPackets *packets = SIDataPackets::bulid()->packets;

    mDevTableWid = new LineTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mDevTableWid);
    mDevTableWid->initPackets(packets);

    mEnvTableWid = new EnvTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mEnvTableWid);
    mEnvTableWid->initPackets(packets);

    mThresholdTableWid = new LineThresholdTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mThresholdTableWid);
    mThresholdTableWid->initPackets(packets);

    mTransTableWid = new TransTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mTransTableWid);
    mTransTableWid->initPackets(packets);
}

void SI_SimulateWid:: simulateSlot(int id)
{
    ComTableWid *wid = nullptr;
    switch (id) {
    case SI_Test_Stop: mSimulateThread->stopThread(); break;
    case SI_Test_Simulate: mSimulateThread->startThread(); break;
    case SI_DevReal_Info: wid = mDevTableWid; break;
    case SI_Trans_Info: wid = mTransTableWid; break;
    case SI_Threshold_Info: wid = mThresholdTableWid; break;
    case SI_Env_Info: wid = mEnvTableWid; break;
    default:  break;
    }

    if(wid) ui->stackedWid->setCurrentWidget(wid);
}
