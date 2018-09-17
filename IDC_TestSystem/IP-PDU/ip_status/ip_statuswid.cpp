#include "ip_statuswid.h"
#include "ui_ip_statuswid.h"
#include "ip_com/ipdatapackets.h"

IP_StatusWid::IP_StatusWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IP_StatusWid)
{
    ui->setupUi(this);
    QTimer::singleShot(100,this,SLOT(initFunSLot())); //延时初始化
}

IP_StatusWid::~IP_StatusWid()
{
    delete ui;
}


void IP_StatusWid::initFunSLot()
{
    sDevPackets *packets = IpDataPackets::bulid()->packets;

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
}

void IP_StatusWid:: simulateSlot(int id)
{
    ComTableWid *wid = nullptr;
    switch (id) {
    case Info_Line: wid = mDevTableWid; break;
    case Info_Trans: wid = mTransTableWid; break;
    case Info_LineThreshold: wid = mThresholdTableWid; break;
    case Info_Env: wid = mEnvTableWid; break;
    default:  break;
    }

    if(wid) ui->stackedWid->setCurrentWidget(wid);
}
