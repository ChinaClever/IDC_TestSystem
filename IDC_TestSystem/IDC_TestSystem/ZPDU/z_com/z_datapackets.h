#ifndef Z_DATAPACKETS_H
#define Z_DATAPACKETS_H
#include "z_configfile.h"

class Z_DataPackets
{
    Z_DataPackets();
public:
    static Z_DataPackets *bulid();

    sDevPackets *packets;
    sDataPacket *getDev(int num);
};

#endif // Z_DATAPACKETS_H
