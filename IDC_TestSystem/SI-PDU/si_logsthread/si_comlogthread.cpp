/*
 * Si 设备数据包的静态类
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "si_comlogthread.h"

SI_ComLogThread::SI_ComLogThread(QObject *parent) : QThread(parent)
{
    mCount = 1;
    isRun = false;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}


SI_ComLogThread::~SI_ComLogThread()
{
    isRun = false;
    wait();
}

SiDevPacket *SI_ComLogThread::getPacket(int id)
{
    return SIDataPackets::bulid()->getDev(id);
}

void SI_ComLogThread::workDown()
{
    int sec = SiConfigFile::bulid()->item->logMins * 60;
    if(mCount++ % sec == 0)
        saveLogs();
}


void SI_ComLogThread::run()
{
    isRun = true;
    workDown();
    isRun = false;
}

void SI_ComLogThread::startThread()
{
    timer->start(1*1000);
}

void SI_ComLogThread::stopThread()
{
    timer->stop();
}

void SI_ComLogThread::timeoutDone()
{
    if(isRun == false) {
        start();
    }
}

void SI_ComLogThread::toolBoxSlot(int id)
{
    switch (id) {
    case SI_Test_Stop:
        stopThread();
        break;

    case SI_Test_Simulate:
        startThread();
        break;
    }
}
