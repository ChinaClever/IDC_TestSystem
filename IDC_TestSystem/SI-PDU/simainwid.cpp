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
    mDpThread = SI_DpThread::bulid(this);
    mRtuThread = new SI_RtuThread(this);
    mServiceThread = new SI_ServiceThread(this);

    timer = new QTimer(this);
    timer->start(1*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
    QTimer::singleShot(100,this,SLOT(initFunSLot())); //延时初始化
}

SIMainWid::~SIMainWid()
{
    delete ui;
}

void SIMainWid::initFunSLot()
{
    mtoolBoxWid = new SI_ToolBoxWid(ui->toolBoxWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), this, SLOT(toolBoxSlot(int)));

    mStatusWid = new SI_StatusWid(ui->stackedWid);
    ui->stackedWid->addWidget(mStatusWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mStatusWid, SLOT(simulateSlot(int)));

    mSetMainWid = new SI_SetMainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mSetMainWid);

    mLogsWid = new SILogsWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogsWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mLogsWid, SLOT(updateWidSlot(int)));
}


void SIMainWid::toolBoxSlot(int id)
{
    if((id >= Info_Line) && (id < Info_Set)) {
        ui->stackedWid->setCurrentWidget(mStatusWid);
    } else if((id >= Log_Modbus) && (id <= Log_Alarm)) {
         ui->stackedWid->setCurrentWidget(mLogsWid);
    } else if(id == Info_Set) {
         ui->stackedWid->setCurrentWidget(mSetMainWid);
    }else {
        switch (id) {
        case Test_Rtu: mRtuThread->startThread(); break;
        case Test_Stop: mRtuThread->stopThread(); break;
        default: break;
        }
    }
}

void SIMainWid::timeoutDone()
{
    sConfigItem *item = SiConfigFile::bulid()->item;
    SIDataPackets::bulid()->packets->devNum = item->devNum;

    if(item->testMode != Test_Stop)
    {
        mDpThread->start();
    }
}
