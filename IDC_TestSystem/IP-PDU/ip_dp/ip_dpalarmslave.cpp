/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ip_dpalarmslave.h"


IP_DpAlarmSlave::IP_DpAlarmSlave(QObject *parent) : DpAlarmSave(parent)
{
    mPackets = IpDataPackets::bulid()->packets;
}


