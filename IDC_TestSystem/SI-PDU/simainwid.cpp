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

    mDevTableWid = new SI_DevTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mDevTableWid);

    mTransTableWid = new SI_TransTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mTransTableWid);

    mThresholdTableWid = new SI_ThresholdTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mThresholdTableWid);

    mEnvTableWid = new SI_EnvTableWid(ui->stackedWid);
    ui->stackedWid->addWidget(mEnvTableWid);

    mLogModbusCmdWid = new SiLogModbusCmdWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogModbusCmdWid);

    mLogModbusTransWid = new SiLogModbusTransWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogModbusTransWid);
    mLogThreads.append(new SI_TransLogThread(this));

    mLogEnvWid = new SiLogEnvWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLogEnvWid);
    mLogThreads.append(new SI_EnvLogThread(this));

    for(int i=0; i<mLogThreads.size(); ++i)
         connect(mtoolBoxWid, SIGNAL(toolBoxSig(int)), mLogThreads.at(i), SLOT(toolBoxSlot(int)));
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

    case SI_DevReal_Info:
        ui->stackedWid->setCurrentWidget(mDevTableWid);
        break;

    case SI_Trans_Info:
        ui->stackedWid->setCurrentWidget(mTransTableWid);
        break;

    case SI_Threshold_Info:
        ui->stackedWid->setCurrentWidget(mThresholdTableWid);
        break;

    case SI_Env_Info:
        ui->stackedWid->setCurrentWidget(mEnvTableWid);
        break;

    case SI_Log_Modbus:
        ui->stackedWid->setCurrentWidget(mLogModbusCmdWid);
        break;

    case SI_Log_Trans:
        ui->stackedWid->setCurrentWidget(mLogModbusTransWid);
        break;

    case SI_Log_Env:
        ui->stackedWid->setCurrentWidget(mLogEnvWid);
        break;

    default:
        break;
    }
}
