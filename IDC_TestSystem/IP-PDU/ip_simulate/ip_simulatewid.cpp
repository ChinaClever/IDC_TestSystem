/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ip_simulatewid.h"
#include "ui_ip_simulatewid.h"

IP_SimulateWid::IP_SimulateWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IP_SimulateWid)
{
    ui->setupUi(this);
    mSimulateThread = new IP_SimulateThread(this);

    QTimer::singleShot(100,this,SLOT(initFunSLot())); //延时初始化
}

IP_SimulateWid::~IP_SimulateWid()
{
    delete ui;
}


void IP_SimulateWid::initFunSLot()
{
    sDevPackets *packets = IpDataPackets::bulid()->packets;

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

void IP_SimulateWid:: simulateSlot(int id)
{
    ComTableWid *wid = nullptr;
    switch (id) {
    case IP_Test_Stop: mSimulateThread->stopThread(); break;
    case IP_Test_Simulate: mSimulateThread->startThread(); break;
    case IP_Info_Dev: wid = mDevTableWid; break;
    case IP_Info_Trans: wid = mTransTableWid; break;
    case IP_Info_Threshold: wid = mThresholdTableWid; break;
    case IP_Info_Env: wid = mEnvTableWid; break;
    default:  break;
    }

    if(wid) ui->stackedWid->setCurrentWidget(wid);
}
