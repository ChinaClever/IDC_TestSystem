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

    QTimer::singleShot(65,this,SLOT(initFunSLot())); //延时初始化
}

BUS_MainWid::~BUS_MainWid()
{
    delete ui;
}

void BUS_MainWid::initFunSLot()
{
    mtoolBoxWid = new BUS_ToolBoxWid(ui->toolBoxWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), this, SLOT(toolBoxSlot(int)));

    mSimulateWid = new BUS_SimulateWid(ui->stackedWid);
    ui->stackedWid->addWidget(mSimulateWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mSimulateWid, SLOT(simulateSlot(int)));

    mLogsWid = new BusLogsWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogsWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mLogsWid, SLOT(updateWidSlot(int)));
}

void BUS_MainWid::toolBoxSlot(int id)
{
    if((id >= BUS_Info_Bus) && (id <= BUS_Info_Set)) {
        ui->stackedWid->setCurrentWidget(mSimulateWid);
    } else if((id >= BUS_Log_Modbus) && (id <= BUS_Log_Alarm)) {
         ui->stackedWid->setCurrentWidget(mLogsWid);
    }
}
