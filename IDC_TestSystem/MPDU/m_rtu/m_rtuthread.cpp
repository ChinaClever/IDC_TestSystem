/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "m_rtuthread.h"

M_RtuThread::M_RtuThread(QObject *parent) : RtuThread(parent)
{

}


M_RtuThread *M_RtuThread::bulid(QObject *parent)
{
    static M_RtuThread* sington = NULL;
    if(sington == NULL) {
        sington = new M_RtuThread(parent);
    }
    return sington;
}

void M_RtuThread::initSlot()
{
    SerialPort *serial = M_ConfigFile::bulid()->item->serial;
    mPackets = M_DataPackets::bulid()->packets;
    mRtu = M_RtuTrans::bulid();

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
void M_RtuThread::writeErrCmd(int id)
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

    M_DpThread::bulid()->saveModbusCmd(list);
}



/**
 * @brief 处理方法
 */
void M_RtuThread::workDown()
{
    int ret = 0;

    sConfigItem *item = M_ConfigFile::bulid()->item;
    mPackets->devNum = item->devNum;

    for(int k=1; k<=mPackets->devNum; ++k)
    {
        int addr = k;
        sDataPacket *dev = &(mPackets->dev[k]);
        for(int i=0; i<ZM_RtuReg_CmdNum - 3; ++i)
        {//跳过MPDU相电压上下限 回路 温湿度上下限 门水烟禁
            if(i==13 || i==14 || (i>=18 && i<=24) || i==35 || i==36 || i==40 || i==41) continue;
            for(int j=0; j< item->cmdModel; ++j) { // 双命令模式
                ret = mRtu->transData(addr, i, dev,item->msecs);
                if(ret) break;
            }
            if((i == 37||i == 38||i == 39)&&ret) {dev->txType |= 0x02;}
            if(isRun && (i>=25 && i<=31))msleep(2000);
            else if(isRun) msleep(1455);
            else return;
        }

        if(ret) { // 正常收到数据
            sentOkCmd(dev->rtuCount);
        } else { // 数据异常
            saveErrCmd(addr, dev->rtuCount);
        }
    }
}
