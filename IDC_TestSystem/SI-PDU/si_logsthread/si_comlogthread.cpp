/*
 * Si 公共日志保存的基类
 *  只需要实现 virtual void saveLogs()=0;
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "si_comlogthread.h"

static QReadWriteLock *gRwLock = new QReadWriteLock();

QReadWriteLock *get_log_lock()
{
    return gRwLock;
}


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

/**
 * @brief 获取设备数据包
 * @param id 设备号
 * @return
 */
SiDevPacket *SI_ComLogThread::getPacket(int id)
{
    return SIDataPackets::bulid()->getDev(id);
}

/**
 * @brief 线程处理的入品方法
 */
void SI_ComLogThread::workDown()
{
    int sec = SiConfigFile::bulid()->item->logMins * 60;
    if(mCount++ % sec == 0)
    {
        msleep(rand() % 300);
        QReadWriteLock *lock = get_log_lock();
        QWriteLocker locker(lock); // 正在操作时不允许关闭
        saveLogs();
    }
}


void SI_ComLogThread::run()
{
    if(isRun == false) {
        isRun = true;
        workDown();
        isRun = false;
    }
}

/**
 * @brief 开启线程
 */
void SI_ComLogThread::startThread()
{
    int time = rand() % 100;
    timer->start(1*1000 + time);
}

/**
 * @brief 停止线程
 */
void SI_ComLogThread::stopThread()
{
    timer->stop();
}

/**
 * @brief 定时启动线程
 */
void SI_ComLogThread::timeoutDone()
{
    if(isRun == false) {
        start();
    }
}

/**
 * @brief
 * @param id
 */
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
