#include "simulatethread.h"

SimulateThread::SimulateThread(QObject *parent) : QThread(parent)
{
    isRun = false;
    mPackets = nullptr;
    QTimer::singleShot(400,this,SLOT(initSlot()));
}

SimulateThread::~SimulateThread()
{
    isRun = false;
    wait();
}




/**
 * @brief 开启线程
 */
void SimulateThread::startThread()
{
    if(!isRun) {
        QTimer::singleShot(100,this,SLOT(start()));  // 启动线程
    }
}

/**
 * @brief 停止线程
 */
void SimulateThread::stopThread()
{
    isRun = false;
    wait();
}

void SimulateThread::setOffLine()
{
    if(mPackets) {
        for(int i=0; i<=mPackets->devNum; ++i) {
            mPackets->dev[i].offLine = 0;
        }
    }
}

void SimulateThread::clearCount()
{
    if(mPackets) {
        for(int i=0; i<=mPackets->devNum; ++i)
        {
            sDataPacket *packet = &(mPackets->dev[i]);
            memset(&(packet->rtuCount), 0, sizeof(sRtuCount));
        }
        mPackets->dev[1].offLine = 1;
    }
}


/**
 * @brief 命令传送成功
 * @param devId
 */
void SimulateThread::sentOkCmd(sRtuCount &count)
{
    count.count++;
    count.okCount ++;

    mDpThread->start();
}


/**
 * @brief 保存失败命令
 * @param devId
 */
void SimulateThread::saveErrCmd(int id, sRtuCount &count)
{
    count.count += 1;
    count.errCount += 1;

    writeErrCmd(id);
}



void SimulateThread::run()
{
    isRun = true;
    clearCount();

    while(isRun) {
        if(mPackets) {
            workDown();
        }
        msleep(10);
    }

    setOffLine();
}

