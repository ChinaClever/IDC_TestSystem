#include "bus_rtuthread.h"
#include "bus_com/bus_configfile.h"

BUS_RtuThread::BUS_RtuThread(QObject *parent) : RtuThread(parent)
{
    mBusId = 0;
}


BUS_RtuThread *BUS_RtuThread::bulid(QObject *parent)
{
    static BUS_RtuThread* sington = NULL;
    if(sington == NULL) {
        sington = new BUS_RtuThread(parent);
    }
    return sington;
}

void BUS_RtuThread::initSlot()
{
    SerialPort *serial = BUS_ConfigFile::bulid()->item->serial;
    mPackets = BusPacketSi::bulid()->getBus(mBusId);
    mRtu = BUS_RtuTrans::bulid();

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
void BUS_RtuThread::writeErrCmd(int id)
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

    BUS_DpThread::bulid(this)->saveModbusCmd(list);
}



/**
 * @brief 处理方法
 */
void BUS_RtuThread::workDown()
{
    int ret = 0;

    sConfigItem *item = BUS_ConfigFile::bulid()->item;
    mPackets->devNum = item->devNum;

    for(int k=0; k<=mPackets->devNum; ++k)
    {
        for(int j=0; j<item->cmdModel; ++j) { // 双命令模式
            ret = mRtu->transmit(k, mPackets, item->msecs);
            if(ret) break;
        }

        sDataPacket *box = &(mPackets->dev[k]);
        if(ret) { // 正常收到数据
            sentOkCmd(box->rtuCount);
        } else { // 数据异常
            saveErrCmd(k, box->rtuCount);
        }

        if(isRun) msleep(755);
        else return;
    }
}
