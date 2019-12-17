#include "mv1_statuswid.h"
#include "ui_mv1_statuswid.h"

MV1_StatusWid::MV1_StatusWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MV1_StatusWid)
{
    ui->setupUi(this);
    QTimer::singleShot(30,this,SLOT(initFunSLot())); //延时初始化
}

MV1_StatusWid::~MV1_StatusWid()
{
    delete ui;
}


void MV1_StatusWid::initFunSLot()
{
    sDevPackets *packets = MV1_DataPackets::bulid()->packets;

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
}

void MV1_StatusWid:: simulateSlot(int id)
{
    ComTableWid *wid = nullptr;
    switch (id) {
    case Info_Line: wid = mDevTableWid; break;
    case Info_Trans: wid = mTransTableWid; break;
    case Info_Output: wid = mOutputTableWid; break;
    case Info_OutputThreshold: wid = mOutputThresholdTableWid; break;
    case Info_LineThreshold: wid = mThresholdTableWid; break;
    case Info_Env: wid = mEnvTableWid; break;
    default:  break;
    }

    if(wid) ui->stackedWid->setCurrentWidget(wid);
}
