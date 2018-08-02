/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ip_simulatethread.h"

IP_SimulateThread::IP_SimulateThread(QObject *parent) : SimulateThread(parent)
{

}



/**
 * @brief 初始化
 */
void IP_SimulateThread::initSlot()
{
    SerialPort *serial = IP_ConfigFile::bulid()->item->serial;
    mDpThread = new IP_DpThread(this);

    mPackets = IpDataPackets::bulid()->packets;
    mRtu = IP_RtuTrans::bulid();
    mRtu->init(serial);
}



/**
 * @brief 保存失败命令
 * @param devId
 */
void IP_SimulateThread::writeErrCmd(int id)
{
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
void IP_SimulateThread::workDown()
{
    int ret = 0;

    IpConfigItem *item = IP_ConfigFile::bulid()->item;
    mPackets->devNum = item->devNum;

    for(int k=1; k<=mPackets->devNum; ++k)
    {
        int addr = k;
        sDataPacket *dev = &(mPackets->dev[k]);
        int v = item->v;
        if(v) v=3; else v = 1;

        for(int j=0; j< item->cmdModel; ++j) { // 双命令模式
            ret = mRtu->transData(addr, v, dev,item->msecs);
            if(ret) break;
        }

        if(ret) { // 正常收到数据
            sentOkCmd(dev->rtuCount);
        } else { // 数据异常
            saveErrCmd(addr, dev->rtuCount);
        }

        if(isRun) msleep(755);
        else return;
    }
}

