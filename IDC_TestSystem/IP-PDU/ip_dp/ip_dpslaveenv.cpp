/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ip_dpslaveenv.h"


IP_DpSlaveEnv::IP_DpSlaveEnv(QObject *parent) : DpSaveEnv(parent)
{
     mPackets = IpDataPackets::bulid()->packets;
}
