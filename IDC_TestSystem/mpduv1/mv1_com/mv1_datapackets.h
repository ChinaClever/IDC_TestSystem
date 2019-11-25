#ifndef MV1_DATAPACKETS_H
#define MV1_DATAPACKETS_H
#include "mv1_configfile.h"

class MV1_DataPackets
{
    MV1_DataPackets();
public:
    static MV1_DataPackets *bulid();

    sDevPackets *packets;
    sDataPacket *getDev(int num);
};

#endif // MV1_DATAPACKETS_H
