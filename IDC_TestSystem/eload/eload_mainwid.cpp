/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: LELoady
 */
#include "eload_mainwid.h"
#include "ui_eload_mainwid.h"
#include "eload_dp/eload_dpthread.h"

ELoad_MainWid::ELoad_MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ELoad_MainWid)
{
    ui->setupUi(this);

    QTimer::singleShot(5,this,SLOT(initFunSLot())); //延时初始化
}

ELoad_MainWid::~ELoad_MainWid()
{
    mRtu->stopThread();//退出线程，防止程序崩溃
    delete ui;
}


void ELoad_MainWid::initFunSLot()
{
    mRtu = IN_RtuThread::bulid(this);

    mtoolBoxWid = new ELoad_ToolBoxWid(ui->toolBoxWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), this, SLOT(toolBoxSlot(int)));

    mHomeMainWid = new ELoad_HomeMainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mHomeMainWid);

    mInputMainWid = new IN_MainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mInputMainWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mInputMainWid, SLOT(updateWidSlot(int)));

    mLogsWid = new ELoad_LogsWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogsWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mLogsWid, SLOT(updateWidSlot(int)));

    ELoad_DpThread::bulid(this)->start();
    mRtu->init(ELoad_ConfigFile::bulid()->item->serial);
    mRtu->startThread();


    mTemRiseWid = new ELoad_TemRiseWid(ui->stackedWid);
    mTemRiseWid->init();
    ui->stackedWid->addWidget(mTemRiseWid);
}

void ELoad_MainWid::toolBoxSlot(int id)
{
    if((id >= ELoad_Info_Trans) && (id <= ELoad_Info_Set)) {
        ui->stackedWid->setCurrentWidget(mInputMainWid);
    } else if((id >= ELoad_Log_Modbus) && (id <= ELoad_Log_Alarm)) {
        ui->stackedWid->setCurrentWidget(mLogsWid);
    }else if((id >= ELoad_Tem_RiseOne) && (id <= ELoad_Tem_RiseThree)) {
        id = id - ELoad_Tem_RiseOne;
        ui->stackedWid->setCurrentWidget(mTemRiseWid);
    }else {
        ui->stackedWid->setCurrentWidget(mHomeMainWid);
    }
}
