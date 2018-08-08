/*
 * Si 设备数据包的静态类
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "sidatapackets.h"

SIDataPackets::SIDataPackets()
{
    packets = new sDevPackets();
    memset(packets, 0, sizeof(sDevPackets));
}

SIDataPackets *SIDataPackets::bulid()
{
    static SIDataPackets* sington = nullptr;
    if(sington == nullptr)
        sington = new SIDataPackets();
    return sington;
}

sDataPacket *SIDataPackets::getDev(int num)
{
    return &(packets->dev[num]);
}
