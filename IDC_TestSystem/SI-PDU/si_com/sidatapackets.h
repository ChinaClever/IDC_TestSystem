#ifndef SIDATAPACKETS_H
#define SIDATAPACKETS_H

#include "si_rtu/si_rtuthread.h"
#include "siconfigfile.h"

class SIDataPackets
{
    SIDataPackets();
public:
    static SIDataPackets *bulid();

    sDevPackets *packets;
    sDataPacket *getDev(int num);
};

#endif // SIDATAPACKETS_H
