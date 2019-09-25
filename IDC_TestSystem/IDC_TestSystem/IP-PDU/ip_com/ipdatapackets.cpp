/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ipdatapackets.h"

IpDataPackets::IpDataPackets()
{
    packets = new sDevPackets();
    memset(packets, 0, sizeof(sDevPackets));
}

IpDataPackets *IpDataPackets::bulid()
{
    static IpDataPackets* sington = nullptr;
    if(sington == nullptr)
        sington = new IpDataPackets();
    return sington;
}

sDataPacket *IpDataPackets::getDev(int num)
{
    return &(packets->dev[num]);
}
