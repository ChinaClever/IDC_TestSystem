/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1_servicethread.h"
#include "mv1_com/mv1_datapackets.h"

MV1_ServiceThread::MV1_ServiceThread(QObject *parent) : WebServiceThread(parent)
{
    mBuildJson = MV1_BuildJson::bulid();
    mPackets = MV1_DataPackets::bulid()->packets;
}
