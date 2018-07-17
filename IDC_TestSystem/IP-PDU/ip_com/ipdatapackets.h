#ifndef IPDATAPACKETS_H
#define IPDATAPACKETS_H
#include "ip_rtu/ip_rtutrans.h"

#define IP_DEV_NUM  100

struct IpDevModubsCount
{
    IpDevModubsCount() {count=okCount=errCount=0;}

    int count;
    int okCount;
    int errCount;
};


struct IpDevPacket
{
    IpDevModubsCount count;
    IP_Rtu_Recv rtuData;
};


class IpDataPackets
{
    IpDataPackets();
public:
    static IpDataPackets *bulid();

    int devNum;
    int lineNum;
    IpDevPacket dev[IP_DEV_NUM];
    IpDevPacket *getDev(int num);
};

#endif // IPDATAPACKETS_H
