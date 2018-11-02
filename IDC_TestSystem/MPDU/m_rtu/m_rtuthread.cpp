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
        for(int i=0; i<ZM_RtuReg_CmdNum-5; ++i)//暂时跳过门禁和水烟禁
        {
            if(i==13||i==14||i==35||i==36) continue;//跳过相电压，温湿度上下限
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
