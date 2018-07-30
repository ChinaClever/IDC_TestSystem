/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ip_servicethread.h"

IP_ServiceThread::IP_ServiceThread(QObject *parent) : QThread(parent)
{
    mBuildJson = IP_BuildJson::bulid();
    mWebSocket = new WebSocketClient(this);

    isRun = false;
    timer = new QTimer(this);
    timer->start(60*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}


IP_ServiceThread::~IP_ServiceThread()
{
    isRun = false;
    wait();
}


void IP_ServiceThread::readDevList()
{
    for(int i=0; i<IP_DEV_NUM; ++i)
    {
        IpDevPacket *packet = IpDataPackets::bulid()->getDev(i);
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

void IP_ServiceThread::timeoutDone()
{
     if(!isRun) run(); //start();
}

void IP_ServiceThread::run()
{
    if(!isRun) {
        isRun = true;
        readDevList();
        isRun = false;
    }
}

