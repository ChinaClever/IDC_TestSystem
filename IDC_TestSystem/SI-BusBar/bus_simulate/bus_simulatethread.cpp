#include "bus_simulatethread.h"
#include "bus_com/bus_configfile.h"
#include "bus_sql/busdbmodbuscmd.h"

BUS_SimulateThread::BUS_SimulateThread(QObject *parent) : QThread(parent)
{
    QTimer::singleShot(500,this,SLOT(initSlot()));
}


BUS_SimulateThread::~BUS_SimulateThread()
{
    isRun = false;
    wait();
}


/**
 * @brief 初始化
 */
void BUS_SimulateThread::initSlot()
{
    SerialPort *serial = BUS_ConfigFile::bulid()->item->serial;
    mDpThread = new BUS_DpThread(this);

    mPacket = BusPacketSi::bulid();
    mRtu = new BUS_RtuTrans();
    mRtu->init(serial);
}

/**
 * @brief 开启线程
 */
void BUS_SimulateThread::startThread()
{
    if(!isRun) {
        QTimer::singleShot(100,this,SLOT(start()));  // 启动线程
    }
}

/**
 * @brief 停止线程
 */
void BUS_SimulateThread::stopThread()
{
    isRun = false;
    //    wait();
}

void BUS_SimulateThread::setOffLine()
{
    for(int i=0; i<BUS_NUM; ++i)
    {
        for(int j=0; j<=BUS_BOX_NUM; ++j) {
            mPacket->getBox(i,j)->offLine = 0;
        }
    }
}

void BUS_SimulateThread::clearCount()
{
    for(int i=0; i<BUS_NUM; ++i)
    {
        for(int j=0; j<=BUS_BOX_NUM; ++j) {
            sBoxData *box = mPacket->getBox(i,j);
            box->count.count = box->count.errCount = box->count.okCount = 0;
        }
    }
}


/**
 * @brief 命令传送成功
 * @param devId
 */
void BUS_SimulateThread::sentOkCmd(BUS_RtuCount &count)
{
    count.count++;
    count.okCount ++;

    mDpThread->start();
}


/**
 * @brief 保存失败命令
 * @param devId
 */
void BUS_SimulateThread::saveErrCmd(int busId, sBoxData *box)
{
    box->count.count += 1;
    box->count.errCount += 1;

    QByteArray array = mRtu->getSentCmd();
    QString strArray = cm_ByteArrayToHexStr(array);
    //    strArray += tr(" (十进制数：");
    //    strArray += cm_ByteArrayToUcharStr(array);
    //    strArray += ")";

    strArray += tr(" (接收数据：");
    array = mRtu->getRecvCmd();
    strArray += cm_ByteArrayToHexStr(array);
    strArray += ")";

    QStringList list;
    list << mPacket->getBusName(busId);
    list << box->name;
    list <<strArray;

    mDpThread->saveModbusCmd(list);
}



/**
 * @brief 处理方法
 */
void BUS_SimulateThread::workDown()
{
    int ret = 0;

    for(int i=0; i<1; ++i) // BUS_NUM
    {
        BusConfigItem *item = BUS_ConfigFile::bulid()->item;
        mPacket->getBus(i)->boxNum = item->devNum; /////========

        for(int k=0; k<=mPacket->getBus(i)->boxNum; ++k)
        {
            int addr = k;
            sBoxData *box = mPacket->getBox(i, k);

            for(int j=0; j<item->cmdModel; ++j) { // 双命令模式
                ret = mRtu->transmit(addr, box, item->msecs);
                if(ret) break;
            }

            if(ret) { // 正常收到数据
                sentOkCmd(box->count);
            } else { // 数据异常
                saveErrCmd(i, box);
            }

            if(isRun) msleep(455);
            else return;
        }
    }
}


void BUS_SimulateThread::run()
{
    isRun = true;
    clearCount();

    while(isRun) {
        workDown();
        msleep(10);;
    }
    setOffLine();
}
