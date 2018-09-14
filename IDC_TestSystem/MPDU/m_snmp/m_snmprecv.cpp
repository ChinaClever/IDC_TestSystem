/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "m_snmprecv.h"

M_SnmpRecv::M_SnmpRecv()
{
    mPackets = M_DataPackets::bulid()->packets;
}


void M_SnmpRecv::devTypeData(int value, sDataPacket *pkt)
{
//    int line=3, loop=6;
//    if((value<5) || ((value>8) &&(value<13))) line = 1;

//    if(value < 5) loop = 2;
//    else if(value < 9) loop = 3;
//    else if(value < 13) loop = 4;

    pkt->data.lineNum = 3;
    pkt->data.loopNum = 2;
    pkt->devSpec = 4;
}
