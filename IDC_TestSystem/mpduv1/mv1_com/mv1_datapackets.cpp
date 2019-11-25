/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1_datapackets.h"

MV1_DataPackets::MV1_DataPackets()
{
    packets = new sDevPackets();
    memset(packets, 0, sizeof(sDevPackets));
}

MV1_DataPackets *MV1_DataPackets::bulid()
{
    static MV1_DataPackets* sington = nullptr;
    if(sington == nullptr)
        sington = new MV1_DataPackets();
    return sington;
}

sDataPacket *MV1_DataPackets::getDev(int num)
{
    return &(packets->dev[num]);
}
