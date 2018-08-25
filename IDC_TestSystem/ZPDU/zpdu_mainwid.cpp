#include "zpdu_mainwid.h"
#include "ui_zpdu_mainwid.h"

ZPDU_MainWid::ZPDU_MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZPDU_MainWid)
{
    ui->setupUi(this);
    QTimer::singleShot(100,this,SLOT(initFunSLot())); //延时初始化
}

ZPDU_MainWid::~ZPDU_MainWid()
{
    delete ui;
}


void ZPDU_MainWid::initFunSLot()
{
    mtoolBoxWid = new Z_ToolBoxWid(ui->toolBoxWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), this, SLOT(toolBoxSlot(int)));

    mSimulateWid = new Z_SimulateWid(ui->stackedWid);
    ui->stackedWid->addWidget(mSimulateWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mSimulateWid, SLOT(simulateSlot(int)));

    mLogsWid = new Z_LogsWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogsWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mLogsWid, SLOT(updateWidSlot(int)));

//    mTestWid = new MTest_MainWid(ui->stackedWid);
//    ui->stackedWid->addWidget(mTestWid);

    mServiceThread = new Z_ServiceThread(this);
}

void ZPDU_MainWid::toolBoxSlot(int id)
{
    if((id >= Z_Info_Dev) && (id < Z_Info_Set)) {
        ui->stackedWid->setCurrentWidget(mSimulateWid);
    } else if((id >= Z_Log_Modbus) && (id <= Z_Log_Alarm)) {
         ui->stackedWid->setCurrentWidget(mLogsWid);
    } else if(id == Z_Info_Set) {
//        ui->stackedWid->setCurrentWidget(mTestWid);
    }
}
