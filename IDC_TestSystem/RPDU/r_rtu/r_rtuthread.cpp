/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "r_rtuthread.h"

R_RtuThread::R_RtuThread(QObject *parent) : RtuThread(parent)
{

}


R_RtuThread *R_RtuThread::bulid(QObject *parent)
{
    static R_RtuThread* sington = NULL;
    if(sington == NULL) {
        sington = new R_RtuThread(parent);
    }
    return sington;
}

void R_RtuThread::initSlot()
{
    SerialPort *serial = R_ConfigFile::bulid()->item->serial;
    mPackets = R_DataPackets::bulid()->packets;
    mRtu = R_RtuTrans::bulid();
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
void R_RtuThread::writeErrCmd(int id)
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

    R_DpThread::bulid()->saveModbusCmd(list);
}



/**
 * @brief 处理方法
 */
void R_RtuThread::workDown()
{
    int ret = 0;

    sConfigItem *item = R_ConfigFile::bulid()->item;
    mPackets->devNum = item->devNum;

    for(int k=1; k<=mPackets->devNum; ++k)
    {
        int addr = k;
        sDataPacket *dev = &(mPackets->dev[k]);
        for(int i=R_RtuReg_CmdNum-1; i>=0; --i)
        {
            for(int j=0; j< item->cmdModel; ++j) { // 双命令模式
                ret = mRtu->transData(addr, i, dev,item->msecs);
                if(ret) break;
            }
            if(isRun) msleep(555);
            else return;
        }

        if(ret) { // 正常收到数据
            sentOkCmd(dev->rtuCount);
        } else { // 数据异常
            saveErrCmd(addr, dev->rtuCount);
        }
    }
}

