#include "si_simulatethread.h"

SI_SimulateThread::SI_SimulateThread(QObject *parent) : QThread(parent)
{
    isRun = false;

    mPackets = SIDataPackets::bulid();
    mRtu = SI_RtuThread::bulid(this);
}

void SI_SimulateThread::init()
{
    SerialPort *serial = SiConfigFile::bulid()->item->serial;
    mRtu->init(serial);
}

SI_SimulateThread::~SI_SimulateThread()
{
    isRun = false;
    wait();
}

void SI_SimulateThread::startThread()
{
    if(!isRun) {
        init();
        QTimer::singleShot(1000,this,SLOT(start()));  // 启动线程
    }
}

void SI_SimulateThread::stopThread()
{
    isRun = false;
    wait();
}

void SI_SimulateThread::workDown()
{
    int ret = 0;
    SiConfigItem *item = SiConfigFile::bulid()->item;

    for(int i=0; i<item->devNum; ++i)
    {
        for(int k=0; k<item->cmdModel; ++k) { // 双命令模式
            ret = mRtu->transData(i+1, item->lineNum, mPackets->getDev(i), item->msecs);
            if(ret) break ;
        }

        if(ret) {

        } else {

        }
    }
}


void SI_SimulateThread::run()
{
    isRun = true;
    while(isRun) {
        workDown();
    }

}
