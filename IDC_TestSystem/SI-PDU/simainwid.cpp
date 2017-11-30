#include "simainwid.h"
#include "ui_simainwid.h"



SIMainWid::SIMainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SIMainWid)
{
    ui->setupUi(this);

    initWid();
    mSimulateThread = new SI_SimulateThread(this);
}

SIMainWid::~SIMainWid()
{
    delete ui;
}

void SIMainWid::initWid()
{
    mtoolBoxWid = new SitoolBoxWid(ui->toolBoxWid);
    connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), this, SLOT(toolBoxSlot(int)));

    mEnvTableWid = new SiEnvTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mEnvTableWid);

    mLogModbusCmdWid = new SiLogModbusCmdWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogModbusCmdWid);

}

void SIMainWid::toolBoxSlot(int id)
{
    switch (id) {
    case SI_Test_Stop:
        mSimulateThread->stopThread();
        break;

    case SI_Test_Simulate:
        mSimulateThread->startThread();
        break;

    case SI_Env_Info:
        ui->stackedWid->setCurrentWidget(mEnvTableWid);
        break;

    case SI_Log_Modbus:
        ui->stackedWid->setCurrentWidget(mLogModbusCmdWid);
        break;

    default:
        break;
    }
}
