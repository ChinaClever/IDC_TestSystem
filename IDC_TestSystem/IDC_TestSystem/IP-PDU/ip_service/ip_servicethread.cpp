/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ip_servicethread.h"
#include "ip_com/ipdatapackets.h"

IP_ServiceThread::IP_ServiceThread(QObject *parent) : WebServiceThread(parent)
{
    mBuildJson = IP_BuildJson::bulid();
    mPackets = IpDataPackets::bulid()->packets;
}


