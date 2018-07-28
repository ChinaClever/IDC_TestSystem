#include "si_servicethread.h"

SI_ServiceThread::SI_ServiceThread(QObject *parent) : QThread(parent)
{
    mBuildJson = SI_BuildJson::bulid();
    mWebSocket = new WebSocketClient(this);

    isRun = false;
    timer = new QTimer(this);
    timer->start(1*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}


SI_ServiceThread::~SI_ServiceThread()
{
    isRun = false;
    wait();
}


void SI_ServiceThread::readDevList()
{
    for(int i=0; i<SI_DEV_NUM; ++i)
    {
        SiDevPacket *packet = SIDataPackets::bulid()->getDev(i);
        if(packet->rtuData.offLine > 0)  // 必须在线才进行检查
        {
            QJsonObject json;
            bool ret = mBuildJson->getJson(packet, json);
            if(ret) {
                ret = mWebSocket->sendMessage(json);               
                 mBuildJson->saveJson("saveTest", json);
            }
        }

        if(!isRun)   return;

//        if(isRun) msleep(10); // 延时1us 让其它线程优先执行
//        else return;
    }
}

void SI_ServiceThread::timeoutDone()
{
     if(!isRun) run(); //start();
}

void SI_ServiceThread::run()
{
    if(!isRun) {
        isRun = true;
        readDevList();
        isRun = false;
    }
}
