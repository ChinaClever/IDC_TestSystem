#ifndef R_DATAPACKETS_H
#define R_DATAPACKETS_H
#include "r_configfile.h"

class R_DataPackets
{
    R_DataPackets();
public:
    static R_DataPackets *bulid();

    sDevPackets *packets;
    sDataPacket *getDev(int num);
};

#endif // R_DATAPACKETS_H
