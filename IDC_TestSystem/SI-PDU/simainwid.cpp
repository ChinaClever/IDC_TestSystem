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
    mRtuThread = SI_RtuThread::bulid(this);
    mServiceThread = new SI_ServiceThread(this);

    timer = new QTimer(this);
    timer->start(1*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
    QTimer::singleShot(40,this,SLOT(initFunSLot())); //延时初始化
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
    if(id < Test_Function)
    {
        switch (id) {
        case Test_Rtu: mRtuThread->startThread(); break;
        case Test_Stop: mRtuThread->stopThread(); break;
        default: break;
        }
    } else if(id <= Test_Datas_Wid) {

    } else if(id < Info_Set) {
         ui->stackedWid->setCurrentWidget(mStatusWid);
    } else if(id == Info_Set) {
        ui->stackedWid->setCurrentWidget(mSetMainWid);
    } else if(id <= Log_Alarm) {
        ui->stackedWid->setCurrentWidget(mLogsWid);
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
