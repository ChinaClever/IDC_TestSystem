/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "si_rtuthread.h"

SI_RtuThread::SI_RtuThread(QObject *parent) : RtuThread(parent)
{

}


/**
 * @brief 初始化
 */
void SI_RtuThread::initSlot()
{
    SerialPort *serial = SiConfigFile::bulid()->item->serial;
    mPackets = SIDataPackets::bulid()->packets;
    mRtu = SI_RtuTrans::bulid(this);
    mRtu->init(serial);
}


/**
 * @brief 保存失败命令
 * @param devId
 */
void SI_RtuThread::writeErrCmd(int id)
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

    SI_DpThread::bulid()->saveModbusCmd(list);
}


/**
 * @brief 处理方法
 */
void SI_RtuThread::workDown()
{
    int ret = 0;
    sConfigItem *item = SiConfigFile::bulid()->item;
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
