#include "ip_rtuthread.h"

IP_RtuThread::IP_RtuThread(QObject *parent) : RtuThread(parent)
{

}


IP_RtuThread *IP_RtuThread::bulid(QObject *parent)
{
    static IP_RtuThread* sington = NULL;
    if(sington == NULL) {
        sington = new IP_RtuThread(parent);
    }
    return sington;
}

/**
 * @brief 初始化
 */
void IP_RtuThread::initSlot()
{
    SerialPort *serial = IP_ConfigFile::bulid()->item->serial;
    mPackets = IpDataPackets::bulid()->packets;
    mRtu = IP_RtuTrans::bulid();
    mRtu->init(serial);
}



/**
 * @brief 保存失败命令
 * @param devId
 */
void IP_RtuThread::writeErrCmd(int id)
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

    IP_DpThread::bulid()->saveModbusCmd(list);
}


/**
 * @brief 处理方法
 */
void IP_RtuThread::workDown()
{
    int ret = 0;

    sConfigItem *item = IP_ConfigFile::bulid()->item;
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
