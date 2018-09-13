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
}

void SIMainWid::initWid()
{
    mtoolBoxWid = new SitoolBoxWid(ui->toolBoxWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), this, SLOT(toolBoxSlot(int)));

    mSimulateWid = new SI_SimulateWid(ui->stackedWid);
    ui->stackedWid->addWidget(mSimulateWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mSimulateWid, SLOT(simulateSlot(int)));

    mSetMainWid = new SI_SetMainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mSetMainWid);

    mLogsWid = new SILogsWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogsWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mLogsWid, SLOT(updateWidSlot(int)));
}

void SIMainWid::toolBoxSlot(int id)
{
    if((id >= Info_Line) && (id < Info_Set)) {
        ui->stackedWid->setCurrentWidget(mSimulateWid);
    } else if((id >= Log_Modbus) && (id <= Log_Alarm)) {
         ui->stackedWid->setCurrentWidget(mLogsWid);
    } else if(id == Info_Set) {
         ui->stackedWid->setCurrentWidget(mSetMainWid);
    }
}
