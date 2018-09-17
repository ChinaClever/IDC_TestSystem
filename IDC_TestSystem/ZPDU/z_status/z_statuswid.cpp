/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "z_statuswid.h"
#include "ui_z_statuswid.h"

Z_StatusWid::Z_StatusWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Z_StatusWid)
{
    ui->setupUi(this);
    QTimer::singleShot(100,this,SLOT(initFunSLot())); //延时初始化
}

Z_StatusWid::~Z_StatusWid()
{
    delete ui;
}


void Z_StatusWid::initFunSLot()
{
    sDevPackets *packets = Z_DataPackets::bulid()->packets;

    mDevTableWid = new LineTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mDevTableWid);
    mDevTableWid->initPackets(packets);

    mOutputTableWid = new OutputTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mOutputTableWid);
    mOutputTableWid->initPackets(packets);

    mEnvTableWid = new EnvTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mEnvTableWid);
    mEnvTableWid->initPackets(packets);

    mThresholdTableWid = new LineThresholdTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mThresholdTableWid);
    mThresholdTableWid->initPackets(packets);

    mTransTableWid = new TransTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mTransTableWid);
    mTransTableWid->initPackets(packets);

    mOutputThresholdTableWid = new OutputThresholdTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mOutputThresholdTableWid);
    mOutputThresholdTableWid->initPackets(packets);

    mLoopTableWid = new LoopTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLoopTableWid);
    mLoopTableWid->initPackets(packets);

    mLoopThresholdTableWid = new LoopThresholdTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLoopThresholdTableWid);
    mLoopThresholdTableWid->initPackets(packets);
}

void Z_StatusWid:: simulateSlot(int id)
{
    ComTableWid *wid = nullptr;
    switch (id) {
    case Info_Line: wid = mDevTableWid; break;
    case Info_Trans: wid = mTransTableWid; break;
    case Info_Loop: wid = mLoopTableWid; break;
    case Info_LoopThreshold: wid = mLoopThresholdTableWid; break;
    case Info_Output: wid = mOutputTableWid; break;
    case Info_OutputThreshold: wid = mOutputThresholdTableWid; break;
    case Info_LineThreshold: wid = mThresholdTableWid; break;
    case Info_Env: wid = mEnvTableWid; break;
    default:  break;
    }

    if(wid) ui->stackedWid->setCurrentWidget(wid);
}
