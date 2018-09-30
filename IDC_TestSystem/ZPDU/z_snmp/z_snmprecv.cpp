#include "z_snmprecv.h"

Z_SnmpRecv::Z_SnmpRecv()
{
    mRate = 10;
    mPackets = Z_DataPackets::bulid()->packets;
}

void Z_SnmpRecv::devTypeData(int value, sDataPacket *pkt)
{
    int line=3, loop=6;
    if((value<5) || ((value>8) &&(value<13))) line = 1;

    if(value < 5) loop = 2;
    else if(value < 9) loop = 3;
    else if(value < 13) loop = 4;

    pkt->data.lineNum = line;
    pkt->data.loopNum = loop;
    pkt->devSpec = value%4;
}
