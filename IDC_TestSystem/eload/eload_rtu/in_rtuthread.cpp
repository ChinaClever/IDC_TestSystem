/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: LELoady
 */
#include "in_rtuthread.h"
#include "eload_dp/eload_dpthread.h"

IN_RtuThread::IN_RtuThread(QObject *parent) : RtuThread(parent)
{

}


IN_RtuThread *IN_RtuThread::bulid(QObject *parent)
{
    static IN_RtuThread* sington = nullptr;
    if(sington == nullptr)
        sington = new IN_RtuThread(parent);
    return sington;
}

void IN_RtuThread::init(SerialPort *serial)
{
    mRtu = IN_RtuTrans::bulid();
    mRtu->init(serial);
}

void IN_RtuThread::initSlot()
{
    mPackets = IN_DataPackets::bulid()->packets;
}

void IN_RtuThread::sentCmd(sRtuSentCom &cmd)
{
    mCmdList.append(cmd);
}

bool IN_RtuThread::sentCmdList()
{
    bool ret = false;
    if(!mCmdList.isEmpty()) {
        sRtuSentCom cmd = mCmdList.first();
        ret = mRtu->sentSetCmd(cmd, 10);
        mCmdList.removeFirst();
    }
    return ret;
}


void IN_RtuThread::writeErrCmd(int id)
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

    ELoad_DpThread::bulid(this)->saveModbusCmd(list);
}

/**
 * @brief 处理方法
 */
void IN_RtuThread::workDown()
{
    int ret = 0, count=1;

    sConfigItem *item = ELoad_ConfigFile::bulid()->item;
    mPackets->devNum = item->devNum;
    if(mRtu->mSerial->isOpened())
    {
        for(int k = 1; k <= mPackets->devNum;  )
        {
            int addr = k;
            sDataPacket *dev = &(mPackets->dev[k]);

            if(mCmdList.size()) {
                sentCmdList();
            } else if(count++%2) {
                mRtu->transgetStatus(addr, dev, item->msecs);
            } else {
                ret = mRtu->transmit(addr, dev, item->msecs);
                if(ret) { // 正常收到数据
                    sentOkCmd(dev->rtuCount);
                } else { // 数据异常
                    saveErrCmd(addr, dev->rtuCount);
                } k++;
            }
        }

        if(isRun) msleep(680);
        else return;
    }

}
