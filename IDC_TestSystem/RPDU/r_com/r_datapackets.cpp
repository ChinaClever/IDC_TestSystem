/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "r_datapackets.h"

R_DataPackets::R_DataPackets()
{
    packets = new sDevPackets();
    memset(packets, 0, sizeof(sDevPackets));
}

R_DataPackets *R_DataPackets::bulid()
{
    static R_DataPackets* sington = nullptr;
    if(sington == nullptr)
        sington = new R_DataPackets();
    return sington;
}

sDataPacket *R_DataPackets::getDev(int num)
{
    return &(packets->dev[num]);
}
