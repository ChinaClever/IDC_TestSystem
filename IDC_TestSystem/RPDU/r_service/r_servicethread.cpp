/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "r_servicethread.h"
#include "r_com/r_datapackets.h"

R_ServiceThread::R_ServiceThread(QObject *parent) : WebServiceThread(parent)
{
    mBuildJson = R_BuildJson::bulid();
    mPackets = R_DataPackets::bulid()->packets;
}
