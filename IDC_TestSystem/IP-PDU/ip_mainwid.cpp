#include "ip_mainwid.h"
#include "ui_ip_mainwid.h"

IP_MainWid::IP_MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IP_MainWid)
{
    ui->setupUi(this);
     QTimer::singleShot(100,this,SLOT(initFunSLot())); //延时初始化
}

IP_MainWid::~IP_MainWid()
{
    delete ui;
}

void IP_MainWid::initFunSLot()
{
//    mtoolBoxWid = new BUS_ToolBoxWid(ui->toolBoxWid);
//    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), this, SLOT(toolBoxSlot(int)));

//    mSimulateWid = new BUS_SimulateWid(ui->stackedWid);
//    ui->stackedWid->addWidget(mSimulateWid);
//    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mSimulateWid, SLOT(simulateSlot(int)));

//    mLogsWid = new BusLogsWid(ui->stackedWid);
//    ui->stackedWid->addWidget(mLogsWid);
//    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mLogsWid, SLOT(updateWidSlot(int)));
}

void IP_MainWid::toolBoxSlot(int id)
{
//    if((id >= BUS_Info_Bus) && (id <= BUS_Info_Set)) {
//        ui->stackedWid->setCurrentWidget(mSimulateWid);
//    } else if((id >= BUS_Log_Modbus) && (id <= BUS_Log_Alarm)) {
//         ui->stackedWid->setCurrentWidget(mLogsWid);
//    }
}
