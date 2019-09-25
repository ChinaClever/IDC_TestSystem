/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "m_datapackets.h"

M_DataPackets::M_DataPackets()
{
    packets = new sDevPackets();
    memset(packets, 0, sizeof(sDevPackets));
}

M_DataPackets *M_DataPackets::bulid()
{
    static M_DataPackets* sington = nullptr;
    if(sington == nullptr)
        sington = new M_DataPackets();
    return sington;
}

sDataPacket *M_DataPackets::getDev(int num)
{
    return &(packets->dev[num]);
}
