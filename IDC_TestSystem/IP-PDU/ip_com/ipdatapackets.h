#ifndef IPDATAPACKETS_H
#define IPDATAPACKETS_H
#include "ip_rtu/ip_rtutrans.h"
#include "ipconfigfile.h"

#define IP_DEV_NUM  100

struct IP_RtuCount
{
    IP_RtuCount() {count=okCount=errCount=0;}

    int count;
    int okCount;
    int errCount;
};


struct IpDevPacket
{
    IP_RtuCount count;
    IP_Rtu_Recv rtuData;
};


class IpDataPackets
{
    IpDataPackets();
public:
    static IpDataPackets *bulid();

    int devNum;
    IpDevPacket dev[IP_DEV_NUM];
    IpDevPacket *getDev(int num);
};

#endif // IPDATAPACKETS_H
