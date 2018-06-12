#include "bus_simulatethread.h"
#include "bus_com/bus_configfile.h"

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

    mPacket = BusPacketSi::bulid();
    mRtu = new BUS_RtuTrans();
    mRtu->init(serial);

    isRun = false;
    timer = new QTimer(this);
    timer->start(1*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));

//    startThread();
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


/**
 * @brief 命令传送成功
 * @param devId
 */
void BUS_SimulateThread::sentOkCmd(BUS_RtuCount &count)
{
    count.count++;
    count.okCount ++;

//    QReadWriteLock *lock = get_log_lock();
//    QWriteLocker locker(lock); // 正在操作时不允许关闭
//    SI_AlarmLogThread::bulid()->saveAlarm(devId);
}


/**
 * @brief 保存失败命令
 * @param devId
 */
void BUS_SimulateThread::saveErrCmd(BUS_RtuCount &count)
{
    count.count += 1;
    count.errCount += 1;

//    QByteArray array = mRtu->getSentCmd();
//    QString strArray = cm_ByteArrayToHexStr(array);
//    strArray += tr(" (十进制数：");
//    strArray += cm_ByteArrayToUcharStr(array);
//    strArray += ")";

//    SiDbModbusCmdItem item;
//    item.dev_id = devId+1;
//    item.msg = strArray;

//    QReadWriteLock *lock = get_log_lock();
//    QWriteLocker locker(lock); // 正在操作时不允许关闭
//    SiDbModbusCmd::bulid()->insertItem(item);
//    msleep(30);
}



/**
 * @brief 处理方法
 */
void BUS_SimulateThread::workDown()
{
    int ret = 0;

    for(int i=0; i<1; ++i)
    {
        ///////=================
//        for(int k=0; k<mPacket->getBus(i)->boxNum; ++k)
            for(int k=0; k<=1; ++k)
        { // 双命令模式
            int addr = k;
            sBoxData *box = mPacket->getBox(i, k);
            ret = mRtu->transmit(addr, box, 10);
            if(ret) { // 正常收到数据
                sentOkCmd(box->count);
            } else { // 数据异常
                saveErrCmd(box->count);
            }

            if(isRun) msleep(455);
            else return;
        }
    }
}


void BUS_SimulateThread::run()
{
//    isRun = true;
//    while(isRun) {
        workDown();
//    }
//    setOffLine();
}

void BUS_SimulateThread::timeoutDone()
{
    if(isRun == false) {
        isRun = true;
         run();
          isRun = false;
    }

}
