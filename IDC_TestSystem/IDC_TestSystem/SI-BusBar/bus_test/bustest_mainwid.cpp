#include "bustest_mainwid.h"
#include "ui_bustest_mainwid.h"
#include "common.h"
BUSTest_MainWid::BUSTest_MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BUSTest_MainWid)
{
    ui->setupUi(this);
    groupBox_background_icon(this);

    mThresholdSetWid = new BUSTEST_ThresholdSetWid(ui->groupBox_2);
    connect(mThresholdSetWid, SIGNAL(updateAddr(int)), this, SLOT(updateAddrSlot(int)));
    connect(mThresholdSetWid, SIGNAL(updateBus(int)), this, SLOT(updateBusSlot(int)));

    mEnvSetWid = new BUSTEST_EnvSetWid(ui->groupBox_3) ;
}


BUSTest_MainWid::~BUSTest_MainWid()
{
    delete ui;
}
void BUSTest_MainWid::updateAddrSlot(int mAddr)
{
    mEnvSetWid->updateAddr(mAddr);

}
void BUSTest_MainWid::updateBusSlot(int mBus)
{
    mEnvSetWid->updateBus(mBus);
}
