#include "ip_simulatethread.h"

IP_SimulateThread::IP_SimulateThread(QObject *parent) : QThread(parent)
{
    QTimer::singleShot(500,this,SLOT(initSlot()));
}


IP_SimulateThread::~IP_SimulateThread()
{
    isRun = false;
    wait();
}


/**
 * @brief 初始化
 */
void IP_SimulateThread::initSlot()
{
    SerialPort *serial = IP_ConfigFile::bulid()->item->serial;
    mDpThread = new IP_DpThread(this);

    mPacket = IpDataPackets::bulid();
    mRtu = IP_RtuTrans::bulid();
    mRtu->init(serial);
}

/**
 * @brief 开启线程
 */
void IP_SimulateThread::startThread()
{
    if(!isRun) {
        QTimer::singleShot(100,this,SLOT(start()));  // 启动线程
    }
}

/**
 * @brief 停止线程
 */
void IP_SimulateThread::stopThread()
{
    isRun = false;
    //    wait();
}

void IP_SimulateThread::setOffLine()
{
    for(int i=0; i<IP_DEV_NUM; ++i)
    {
        mPacket->getDev(i)->rtuData.offLine = 0;
    }
}

void IP_SimulateThread::clearCount()
{
    for(int i=0; i<IP_DEV_NUM; ++i)
    {
        IpDevPacket *packet = mPacket->getDev(i);
        memset(&(packet->count), 0, sizeof(IP_RtuCount));
    }
}


/**
 * @brief 命令传送成功
 * @param devId
 */
void IP_SimulateThread::sentOkCmd(IP_RtuCount &count)
{
    count.count++;
    count.okCount ++;

    mDpThread->start();
}


/**
 * @brief 保存失败命令
 * @param devId
 */
void IP_SimulateThread::saveErrCmd(int id, IP_RtuCount &count)
{
    count.count += 1;
    count.errCount += 1;

    QByteArray array = mRtu->getSentCmd();
    QString strArray = cm_ByteArrayToHexStr(array);

    strArray += tr(" (接收数据：");
    array = mRtu->getRecvCmd();
    strArray += cm_ByteArrayToHexStr(array);
    strArray += ")";

    QStringList list;
    list << QString::number(id);
    list << strArray;

    mDpThread->saveModbusCmd(list);
}


/**
 * @brief 处理方法
 */
void IP_SimulateThread::workDown()
{
    int ret = 0;

    IpConfigItem *item = IP_ConfigFile::bulid()->item;
    mPacket->devNum = item->devNum;

    for(int k=0; k<=mPacket->devNum; ++k)
    {
        int addr = k;
        IpDevPacket *dev = mPacket->getDev(k);
        int v = item->v;
        if(v) v=3; else v = 1;

        for(int j=0; j< item->cmdModel; ++j) { // 双命令模式
            ret = mRtu->transData(addr, v, &(dev->rtuData),item->msecs);
            if(ret) break;
        }

        if(ret) { // 正常收到数据
            sentOkCmd(dev->count);
        } else { // 数据异常
            saveErrCmd(addr, dev->count);
        }

        if(isRun) msleep(755);
        else return;
    }
}


void IP_SimulateThread::run()
{
    isRun = true;
    clearCount();

    while(isRun) {
        workDown();
        msleep(10);;
    }
    setOffLine();
}
