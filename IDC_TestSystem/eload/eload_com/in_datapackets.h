#ifndef I_DATAPACKETS_H
#define I_DATAPACKETS_H
#include "eload_configfile.h"

class IN_DataPackets
{
    IN_DataPackets();
public:
    static IN_DataPackets *bulid();

    sDevPackets *packets;
    sDataPacket *getDev(int num);

    int getTgValue(int mode);
};

#endif // I_DATAPACKETS_H