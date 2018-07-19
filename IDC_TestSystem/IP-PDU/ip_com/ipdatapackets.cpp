/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ipdatapackets.h"

IpDataPackets::IpDataPackets()
{
    memset(&dev, 0, sizeof(IpDevPacket)*IP_DEV_NUM);
    devNum = 0;
}

IpDataPackets *IpDataPackets::bulid()
{
    static IpDataPackets* sington = nullptr;
    if(sington == nullptr)
        sington = new IpDataPackets();
    return sington;
}

IpDevPacket *IpDataPackets::getDev(int num)
{
    return &(dev[num]);
}
