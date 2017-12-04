#ifndef SIDATAPACKETS_H
#define SIDATAPACKETS_H

#include "si_rtu/si_rtuthread.h"
#include "siconfigfile.h"

#define SI_DEV_NUM  100

struct SiDevModubsCount
{
    SiDevModubsCount() {count=okCount=errCount=0;}

    int count;
    int okCount;
    int errCount;
};


struct SiDevPacket
{
    SiDevPacket() {}

    SiDevModubsCount count;
    SI_Rtu_Recv rtuData;
};

class SIDataPackets
{
    SIDataPackets();
public:
     static SIDataPackets *bulid();

    SiDevPacket dev[SI_DEV_NUM];
    SiDevPacket *getDev(int num);
};

#endif // SIDATAPACKETS_H
