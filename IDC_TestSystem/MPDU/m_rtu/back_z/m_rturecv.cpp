/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "m_rturecv.h"

M_RtuRecv::M_RtuRecv()
{

}


void M_RtuRecv::devTypeData(uchar *buf, int len, ZM_sRtuPacket &pkt)
{
    ushort array[3] = {0};
    rtuRecvData(buf, len, array);

    int value = array[0], line=3, loop=0;
//    if((value<5) || ((value>8) &&(value<13))) line = 1;

//    if(value < 5) loop = 2;
//    else if(value < 9) loop = 3;
//    else if(value < 13) loop = 4;

    pkt.line.num = line;
    pkt.loop.num = loop;
    pkt.output.num = 24;
    pkt.devSpec = value%4;
}
