#include "in_rtuthread.h"

IN_RtuThread::IN_RtuThread(QObject *parent) : SimulateThread(parent)
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

void IN_RtuThread::sentCmdList()
{
    if(mCmdList.size() > 0) {
        sRtuSentCom cmd = mCmdList.first();
        bool ret = mRtu->sentSetCmd(cmd, 10);
        if(ret) mCmdList.removeFirst();
    }
}

/**
 * @brief 处理方法
 */
void IN_RtuThread::workDown()
{
    int ret = 0;

    sentCmdList();
    sELoad_ConfigItem *item = ELoad_ConfigFile::bulid()->item;
    mPackets->devNum = item->devNum;

    for(int k=1; k<=mPackets->devNum; ++k)
    {
        int addr = k;
        sDataPacket *dev = &(mPackets->dev[k]);
        ret = mRtu->transmit(addr, dev, item->msecs);

        if(isRun) msleep(455);
        else return;
        if(!ret) break;

        if(ret) { // 正常收到数据
            sentOkCmd(dev->rtuCount);
        } else { // 数据异常
            saveErrCmd(addr, dev->rtuCount);
        }
    }
}
