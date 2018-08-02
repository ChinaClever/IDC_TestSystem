/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "si_servicethread.h"

SI_ServiceThread::SI_ServiceThread(QObject *parent) : WebServiceThread(parent)
{
    mBuildJson = SI_BuildJson::bulid();
    mPackets = SIDataPackets::bulid()->packets;
}


