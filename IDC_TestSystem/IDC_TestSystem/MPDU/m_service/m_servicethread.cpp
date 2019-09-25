/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "m_servicethread.h"
#include "m_com/m_datapackets.h"

M_ServiceThread::M_ServiceThread(QObject *parent) : WebServiceThread(parent)
{
    mBuildJson = M_BuildJson::bulid();
    mPackets = M_DataPackets::bulid()->packets;
}
