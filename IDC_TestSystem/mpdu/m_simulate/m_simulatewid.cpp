#include "m_simulatewid.h"
#include "ui_m_simulatewid.h"

M_SimulateWid::M_SimulateWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::M_SimulateWid)
{
    ui->setupUi(this);

    QTimer::singleShot(100,this,SLOT(initFunSLot())); //延时初始化
}

M_SimulateWid::~M_SimulateWid()
{
    delete ui;
}

void M_SimulateWid::initFunSLot()
{
    sDevPackets *packets = M_DataPackets::bulid()->packets;

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

    mOutputTableWid = new OutputTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mOutputTableWid);
    mOutputTableWid->initPackets(packets);

    mOutputThresholdTableWid = new OutputThresholdTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mOutputThresholdTableWid);
    mOutputThresholdTableWid->initPackets(packets);
}

void M_SimulateWid:: simulateSlot(int id)
{
    ComTableWid *wid = nullptr;
    switch (id) {
    //    case M_Test_Stop: mSimulateThread->stopThread(); break;
    //    case M_Test_Simulate: mSimulateThread->startThread(); break;
    case M_Info_Dev: wid = mDevTableWid; break;
    case M_Info_Trans: wid = mTransTableWid; break;
    case M_Info_Output: wid = mOutputTableWid; break;
    case M_Info_OutputThreshold: wid = mOutputThresholdTableWid; break;
    case M_Info_Threshold: wid = mThresholdTableWid; break;
    case M_Info_Env: wid = mEnvTableWid; break;
    default:  break;
    }

    if(wid) ui->stackedWid->setCurrentWidget(wid);
}
