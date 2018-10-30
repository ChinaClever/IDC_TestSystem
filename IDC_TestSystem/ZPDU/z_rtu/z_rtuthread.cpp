/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "z_rtuthread.h"

Z_RtuThread::Z_RtuThread(QObject *parent) : RtuThread(parent)
{

}


Z_RtuThread *Z_RtuThread::bulid(QObject *parent)
{
    static Z_RtuThread* sington = NULL;
    if(sington == NULL) {
        sington = new Z_RtuThread(parent);
    }
    return sington;
}

void Z_RtuThread::initSlot()
{
    SerialPort *serial = Z_ConfigFile::bulid()->item->serial;
    mPackets = Z_DataPackets::bulid()->packets;
    mRtu = Z_RtuTrans::bulid();
    mRtu->init(serial);
}


/**
 * @brief 保存失败命令
 * @param devId
 */
void Z_RtuThread::writeErrCmd(int id)
{
    QByteArray array = mRtu->getSentCmd();
    QString strArray = cm_ByteArrayToHexStr(array);

    strArray += tr(" (接收数据");
    array = mRtu->getRecvCmd();
    strArray += " len=" +QString::number(array.size()) +": ";
    strArray += cm_ByteArrayToHexStr(array);
    strArray += ")";

    QStringList list;
    list << QString::number(id);
    list << strArray;

    Z_DpThread::bulid()->saveModbusCmd(list);
}



/**
 * @brief 处理方法
 */
void Z_RtuThread::workDown()
{
    int ret = 0;

    sConfigItem *item = Z_ConfigFile::bulid()->item;
    mPackets->devNum = item->devNum;

    for(int k=1; k<=mPackets->devNum; ++k)
    {
        int addr = k;
        sDataPacket *dev = &(mPackets->dev[k]);
        for(int i=0; i<Z_RtuReg_CmdNum; ++i)
        {
            for(int j=0; j< item->cmdModel; ++j) { // 双命令模式
                ret = mRtu->transData(addr, i, dev,item->msecs);
                if(ret) break;
            }
            if(isRun) msleep(455);
            else return;
            if(!ret) break;
        }

        if(ret) { // 正常收到数据
            sentOkCmd(dev->rtuCount);
        } else { // 数据异常
            saveErrCmd(addr, dev->rtuCount);
        }
    }
}

