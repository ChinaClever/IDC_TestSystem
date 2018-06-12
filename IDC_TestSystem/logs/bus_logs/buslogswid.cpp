#include "buslogswid.h"
#include "ui_buslogswid.h"

BusLogsWid::BusLogsWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BusLogsWid)
{
    ui->setupUi(this);

//    QTimer::singleShot(100,this,SLOT(initFunSLot())); //延时初始化
}

BusLogsWid::~BusLogsWid()
{
    delete ui;
}


//void BUS_SimulateWid::initFunSLot()
//{
//    mBusTableWid = new BUS_BusTableWid(ui->stackedWid);
//    ui->stackedWid->addWidget(mBusTableWid);
//    connect(this, SIGNAL(updateSig()), mBusTableWid, SLOT(updateData()));

//    mBoxTableWid = new BUS_BoxTableWid(ui->stackedWid);
//    ui->stackedWid->addWidget(mBoxTableWid);
//    connect(this, SIGNAL(updateSig()), mBoxTableWid, SLOT(updateData()));

//    mLoopTableWid = new BUS_LoopTableWid(ui->stackedWid);
//    ui->stackedWid->addWidget(mLoopTableWid);
//    connect(this, SIGNAL(updateSig()), mLoopTableWid, SLOT(updateData()));

//    mTransTableWid = new BUS_TransTableWid(ui->stackedWid);
//    ui->stackedWid->addWidget(mTransTableWid);
//    connect(this, SIGNAL(updateSig()), mTransTableWid, SLOT(updateData()));

//    mThresholdTableWid = new BUS_ThresholdTableWid(ui->stackedWid);
//    ui->stackedWid->addWidget(mThresholdTableWid);
//    connect(this, SIGNAL(updateSig()), mThresholdTableWid, SLOT(updateData()));

//    mEnvTableWid = new BUS_EnvTableWid(ui->stackedWid);
//    ui->stackedWid->addWidget(mEnvTableWid);
//    connect(this, SIGNAL(updateSig()), mEnvTableWid, SLOT(updateData()));
//}

//void BUS_SimulateWid:: simulateSlot(int id)
//{
//    BUS_LoopTableWid *wid = nullptr;
//    switch (id) {
//    case BUS_Info_Bus: wid = mBusTableWid; break;
//    case BUS_Info_Box: wid = mBoxTableWid; break;
//    case BUS_Info_Loop: wid = mLoopTableWid; break;
//    case BUS_Info_Trans: wid = mTransTableWid; break;
//    case BUS_Info_Threshold: wid = mThresholdTableWid; break;
//    case BUS_Info_Env: wid = mEnvTableWid; break;
//    default:  break;
//    }

//    if(wid) ui->stackedWid->setCurrentWidget(wid);
//}
