#include "sidatapackets.h"

SIDataPackets::SIDataPackets()
{
    memset(&dev, 0, sizeof(SiDevPacket)*SI_DEV_NUM);
}

SIDataPackets *SIDataPackets::bulid()
{
    static SIDataPackets* sington = nullptr;
    if(sington == nullptr)
        sington = new SIDataPackets();
    return sington;
}

SiDevPacket *SIDataPackets::getDev(int num)
{
    return &(dev[num]);
}
