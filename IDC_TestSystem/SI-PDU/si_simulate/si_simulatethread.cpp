#include "si_simulatethread.h"
#include "si_sql/sidbmodbuscmd.h"

SI_SimulateThread::SI_SimulateThread(QObject *parent) : QThread(parent)
{
    isRun = false;

    mPackets = SIDataPackets::bulid();
    mRtu = SI_RtuThread::bulid(this);
}

void SI_SimulateThread::init()
{
    SerialPort *serial = SiConfigFile::bulid()->item->serial;
    mRtu->init(serial);
}

SI_SimulateThread::~SI_SimulateThread()
{
    isRun = false;
    wait();
}

void SI_SimulateThread::startThread()
{
    if(!isRun) {
        init();
        QTimer::singleShot(1000,this,SLOT(start()));  // 启动线程
    }
}

void SI_SimulateThread::stopThread()
{
    isRun = false;
    wait();
}

void SI_SimulateThread::sentOkCmd(int devId)
{
    SiDevPacket *dev = mPackets->getDev(devId);
    SiDevModubsCount *count = &(dev->count);
    count->count++;
    count->okCount ++;
}



void SI_SimulateThread::saveErrCmd(int devId)
{
    SiDevPacket *dev = mPackets->getDev(devId);
    SiDevModubsCount *count = &(dev->count);
    count->count++;
    count->errCount ++;

    QByteArray array = mRtu->getSentCmd();
    QString strArray = cm_ByteArrayToHexStr(array);
    strArray += tr(" (十进制数：");
    strArray += cm_ByteArrayToUcharStr(array);
    strArray += ")";

    SiDbModbusCmdItem item;
    item.dev_id = devId+1;
    item.msg = strArray;
    SiDbModbusCmd::bulid()->insertItem(item);
    msleep(5);
}



void SI_SimulateThread::workDown()
{
    int ret = 0;
    SiConfigItem *item = SiConfigFile::bulid()->item;

    for(int i=0; i<item->devNum; ++i)
    {
        for(int k=0; k<item->cmdModel; ++k) { // 双命令模式
            ret = mRtu->transData(i+1, item->lineNum, &(mPackets->getDev(i)->rtuData), item->msecs);
            if(ret) break ;
        }

        if(ret) { // 正常收到数据
            sentOkCmd(i);
        } else { // 数据异常
            saveErrCmd(i);
        }
    }
}


void SI_SimulateThread::run()
{
    isRun = true;
    while(isRun) {
        workDown();
    }
}
