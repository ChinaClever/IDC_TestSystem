#ifndef IPDATAPACKETS_H
#define IPDATAPACKETS_H
#include "ip_rtu/ip_rtutrans.h"
#include "ipconfigfile.h"


class IpDataPackets
{
    IpDataPackets();
public:
    static IpDataPackets *bulid();

    sDevPackets *packets;
    sDataPacket *getDev(int num);
};

#endif // IPDATAPACKETS_H
