#ifndef M_DATAPACKETS_H
#define M_DATAPACKETS_H
#include "m_configfile.h"

class M_DataPackets
{
    M_DataPackets();
public:
    static M_DataPackets *bulid();

    sDevPackets *packets;
    sDataPacket *getDev(int num);
};

#endif // M_DATAPACKETS_H
