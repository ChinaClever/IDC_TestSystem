/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "in_mainwid.h"
#include "ui_in_mainwid.h"
#include "eload_rtu/in_rtuthread.h"

IN_MainWid::IN_MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IN_MainWid)
{
    ui->setupUi(this);
    QTimer::singleShot(50,this,SLOT(initFunSLot())); //延时初始化
}

IN_MainWid::~IN_MainWid()
{
    delete ui;
}

void IN_MainWid::initWidget()
{
    sDevPackets *packets = IN_DataPackets::bulid()->packets;

    mInputTableWid = new IN_InputTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mInputTableWid);
    mInputTableWid->initPackets(packets);

    mInputThresholdTableWid = new IN_InputThresholdTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mInputThresholdTableWid);
    mInputThresholdTableWid->initPackets(packets);

    mTransTableWid = new TransTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mTransTableWid);
    mTransTableWid->initPackets(packets);

    mEnvTableWid = new IN_EnvTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mEnvTableWid);
    mEnvTableWid->initPackets(packets);

    mSetMainWid = new IN_setMainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mSetMainWid);
}

void IN_MainWid::initFunSLot()
{
    initWidget();
}


void IN_MainWid:: updateWidSlot(int id)
{
    ComTableWid *wid = nullptr;
    switch (id) {
    case ELoad_Info_Input: wid = mInputTableWid; break;
    case ELoad_Info_InputThreshold: wid = mInputThresholdTableWid; break;
    case ELoad_Info_Trans: wid = mTransTableWid; break;
    case ELoad_Info_Env: wid = mEnvTableWid; break;
    case ELoad_Info_Set: ui->stackedWid->setCurrentWidget(mSetMainWid); break;
    default:  break;
    }

    if(wid) ui->stackedWid->setCurrentWidget(wid);
}

