/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: LELoady
 */
#include "eload_mainwid.h"
#include "ui_eload_mainwid.h"
#include "eload_rtu/in_rtuthread.h"

ELoad_MainWid::ELoad_MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ELoad_MainWid)
{
    ui->setupUi(this);

    QTimer::singleShot(5,this,SLOT(initFunSLot())); //延时初始化
}

ELoad_MainWid::~ELoad_MainWid()
{
    delete ui;
}


void ELoad_MainWid::initFunSLot()
{
    IN_RtuThread *rtu = IN_RtuThread::bulid(this);
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

    rtu->init(ELoad_ConfigFile::bulid()->item->serial);
    //rtu->startThread();
}

void ELoad_MainWid::toolBoxSlot(int id)
{
    if((id >= ELoad_Info_Trans) && (id <= ELoad_Info_Set)) {
        ui->stackedWid->setCurrentWidget(mInputMainWid);
    } else if((id >= ELoad_Log_Modbus) && (id <= ELoad_Log_Alarm)) {
        ui->stackedWid->setCurrentWidget(mLogsWid);
    }else {
        ui->stackedWid->setCurrentWidget(mHomeMainWid);
    }
}
