/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "bus_mainwid.h"
#include "ui_bus_mainwid.h"

BUS_MainWid::BUS_MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BUS_MainWid)
{
    ui->setupUi(this);
    QTimer::singleShot(100,this,SLOT(initFunSLot())); //延时初始化
}

BUS_MainWid::~BUS_MainWid()
{
    delete ui;
}

void BUS_MainWid::initFunSLot()
{
    mtoolBoxWid = new BUS_ToolBoxWid(ui->toolBoxWid);

    mBusTableWid = new BUS_BusTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mBusTableWid);

    mBoxTableWid = new BUS_BoxTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mBoxTableWid);

    mLoopTableWid = new BUS_LoopTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLoopTableWid);

    mTransTableWid = new BUS_TransTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mTransTableWid);

    mThresholdTableWid = new BUS_ThresholdTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mThresholdTableWid);

    mEnvTableWid = new BUS_EnvTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mEnvTableWid);
}
