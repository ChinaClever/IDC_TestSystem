/*
 * Si 模拟测试线程
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "si_simulatethread.h"
#include "si_sql/sidbmodbuscmd.h"
#include "si_logsthread/si_alarmlogthread.h"

SI_SimulateThread::SI_SimulateThread(QObject *parent) : QThread(parent)
{
    isRun = false;
    QTimer::singleShot(400,this,SLOT(initSlot()));
}

SI_SimulateThread::~SI_SimulateThread()
{
    isRun = false;
    wait();
}


/**
 * @brief 初始化
 */
void SI_SimulateThread::initSlot()
{
    SerialPort *serial = SiConfigFile::bulid()->item->serial;

    mDpThread = new SI_DpThread(this);
    mPackets = SIDataPackets::bulid()->packets;
    mRtu = SI_RtuThread::bulid(this);
    mRtu->init(serial);
}

/**
 * @brief 开启线程
 */
void SI_SimulateThread::startThread()
{
    if(!isRun) {
        QTimer::singleShot(100,this,SLOT(start()));  // 启动线程
    }
}

/**
 * @brief 停止线程
 */
void SI_SimulateThread::stopThread()
{
    isRun = false;
    //    wait();
}

void SI_SimulateThread::setOffLine()
{
    for(int i=0; i<mPackets->devNum; ++i) {
        mPackets->dev[i].offLine = 0;
    }
}

void SI_SimulateThread::clearCount()
{
    for(int i=0; i<mPackets->devNum; ++i)
    {
        sDataPacket *packet = &(mPackets->dev[i]);
        memset(&(packet->rtuCount), 0, sizeof(sRtuCount));
    }
}


/**
 * @brief 命令传送成功
 * @param devId
 */
void SI_SimulateThread::sentOkCmd(sRtuCount &count)
{
    count.count++;
    count.okCount ++;

    mDpThread->start();
}


/**
 * @brief 保存失败命令
 * @param devId
 */
void SI_SimulateThread::saveErrCmd(int id, sRtuCount &count)
{
    count.count += 1;
    count.errCount += 1;

    QByteArray array = mRtu->getSentCmd();
    QString strArray = cm_ByteArrayToHexStr(array);

    strArray += tr(" (接收数据：");
    array = mRtu->getRecvCmd();
    strArray += cm_ByteArrayToHexStr(array);
    strArray += ")";

    QStringList list;
    list << QString::number(id);
    list << strArray;

    mDpThread->saveModbusCmd(list);
}


/**
 * @brief 处理方法
 */
void SI_SimulateThread::workDown()
{
    int ret = 0;
    SiConfigItem *item = SiConfigFile::bulid()->item;
    mPackets->devNum = item->devNum;

    for(int i=1; i<=mPackets->devNum; ++i)
    {
        sDataPacket *pkt = &(mPackets->dev[i]);
        for(int k=0; k<item->cmdModel; ++k) { // 双命令模式
            ret = mRtu->transData(i, item->lineNum, pkt, item->msecs);
            if(ret) break ;
        }

        if(ret) { // 正常收到数据
            sentOkCmd(pkt->rtuCount);
        } else { // 数据异常
            saveErrCmd(i, pkt->rtuCount);
        }

        if(isRun) msleep(455);
        else break;
    }
}


void SI_SimulateThread::run()
{
    isRun = true;
    clearCount();
    while(isRun) {
        workDown();
    }
    setOffLine();
}
