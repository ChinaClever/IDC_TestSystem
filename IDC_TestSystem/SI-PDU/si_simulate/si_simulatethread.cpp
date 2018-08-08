/*
 * Si 模拟测试线程
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "si_simulatethread.h"
#include "si_sql/sidbmodbuscmd.h"

SI_SimulateThread::SI_SimulateThread(QObject *parent) : SimulateThread(parent)
{

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
 * @brief 保存失败命令
 * @param devId
 */
void SI_SimulateThread::writeErrCmd(int id)
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


