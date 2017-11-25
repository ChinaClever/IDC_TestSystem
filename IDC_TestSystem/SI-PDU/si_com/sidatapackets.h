#ifndef SIDATAPACKETS_H
#define SIDATAPACKETS_H

#include "si_rtu/si_rtuthread.h"
#include "siconfigfile.h"

#define SI_DEV_NUM  32

typedef SI_Rtu_Recv SiDevPacket;

class SIDataPackets
{
    SIDataPackets();
public:
     static SIDataPackets *bulid();

    SiDevPacket dev[SI_DEV_NUM];
    SiDevPacket *getDev(int num);
};

#endif // SIDATAPACKETS_H
