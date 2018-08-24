#include "z_simulatewid.h"
#include "ui_z_simulatewid.h"

Z_SimulateWid::Z_SimulateWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Z_SimulateWid)
{
    ui->setupUi(this);
    mSimulateThread = new Z_SimulateThread(this);
    QTimer::singleShot(100,this,SLOT(initFunSLot())); //延时初始化
}

Z_SimulateWid::~Z_SimulateWid()
{
    delete ui;
}


void Z_SimulateWid::initFunSLot()
{
    sDevPackets *packets = Z_DataPackets::bulid()->packets;

    mOutputTableWid = new OutputTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mOutputTableWid);
    mOutputTableWid->initPackets(packets);

    mDevTableWid = new LineTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mDevTableWid);
    mDevTableWid->initPackets(packets);

    mEnvTableWid = new EnvTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mEnvTableWid);
    mEnvTableWid->initPackets(packets);

    mThresholdTableWid = new LineThresholdTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mThresholdTableWid);
    mThresholdTableWid->initPackets(packets);

    mTransTableWid = new TransTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mTransTableWid);
    mTransTableWid->initPackets(packets);

    mOutputThresholdTableWid = new OutputThresholdTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mOutputThresholdTableWid);
    mOutputThresholdTableWid->initPackets(packets);

    mLoopTableWid = new LoopTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLoopTableWid);
    mLoopTableWid->initPackets(packets);

    mLoopThresholdTableWid = new LoopThresholdTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLoopThresholdTableWid);
    mLoopThresholdTableWid->initPackets(packets);
}

void Z_SimulateWid:: simulateSlot(int id)
{
    ComTableWid *wid = nullptr;
    switch (id) {
    case Z_Test_Stop: mSimulateThread->stopThread(); break;
    case Z_Test_Simulate: mSimulateThread->startThread(); break;
    case Z_Info_Dev: wid = mDevTableWid; break;
    case Z_Info_Trans: wid = mTransTableWid; break;
    case Z_Info_Loop: wid = mLoopTableWid; break;
    case Z_Info_LoopThreshold: wid = mLoopThresholdTableWid; break;
    case Z_Info_Output: wid = mOutputTableWid; break;
    case Z_Info_OutputThreshold: wid = mOutputThresholdTableWid; break;
    case Z_Info_Threshold: wid = mThresholdTableWid; break;
    case Z_Info_Env: wid = mEnvTableWid; break;
    default:  break;
    }

    if(wid) ui->stackedWid->setCurrentWidget(wid);
}
