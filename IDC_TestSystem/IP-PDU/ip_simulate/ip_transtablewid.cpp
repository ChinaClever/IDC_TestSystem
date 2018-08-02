/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ip_transtablewid.h"

IP_TransTableWid::IP_TransTableWid(QWidget *parent) : TransTableWid(parent)
{
     mPackets = IpDataPackets::bulid()->packets;
}
