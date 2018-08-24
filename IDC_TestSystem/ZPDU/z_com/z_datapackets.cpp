#include "z_datapackets.h"

Z_DataPackets::Z_DataPackets()
{
    packets = new sDevPackets();
    memset(packets, 0, sizeof(sDevPackets));
}

Z_DataPackets *Z_DataPackets::bulid()
{
    static Z_DataPackets* sington = nullptr;
    if(sington == nullptr)
        sington = new Z_DataPackets();
    return sington;
}

sDataPacket *Z_DataPackets::getDev(int num)
{
    return &(packets->dev[num]);
}
