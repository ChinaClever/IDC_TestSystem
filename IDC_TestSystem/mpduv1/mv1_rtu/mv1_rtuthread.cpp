/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1_rtuthread.h"

MV1_RtuThread::MV1_RtuThread(QObject *parent) : RtuThread(parent)
{

}


MV1_RtuThread *MV1_RtuThread::bulid(QObject *parent)
{
    static MV1_RtuThread* sington = NULL;
    if(sington == NULL) {
        sington = new MV1_RtuThread(parent);
    }
    return sington;
}

void MV1_RtuThread::initSlot()
{
    SerialPort *serial = MV1_ConfigFile::bulid()->item->serial;
    mPackets = MV1_DataPackets::bulid()->packets;
    mRtu = MV1_RtuTrans::bulid();
    if(serial) {
        mRtu->init(serial);
    } else {
         QTimer::singleShot(1400,this,SLOT(initSlot()));
    }
}


/**
 * @brief 保存失败命令
 * @param devId
 */
void MV1_RtuThread::writeErrCmd(int id)
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

    MV1_DpThread::bulid()->saveModbusCmd(list);
}



/**
 * @brief 处理方法
 */
void MV1_RtuThread::workDown()
{
    int ret = 0;

    sConfigItem *item = MV1_ConfigFile::bulid()->item;
    mPackets->devNum = item->devNum;

    for(int k=1; k<=mPackets->devNum; ++k)
    {
        int addr = k;
        sDataPacket *dev = &(mPackets->dev[k]);
        for(int i=0; i<11; ++i)
        {
            for(int j=0; j< item->cmdModel; ++j) { // 双命令模式
                ret = mRtu->transData(addr, i, dev,item->msecs);
                if(ret) break;
            }
            if(isRun) msleep(755);
            else return;
            if(i == 9&&ret) dev->txType |= 0x02;
        }

        if(ret) { // 正常收到数据
            sentOkCmd(dev->rtuCount);
        } else { // 数据异常
            saveErrCmd(addr, dev->rtuCount);
        }
    }
}
