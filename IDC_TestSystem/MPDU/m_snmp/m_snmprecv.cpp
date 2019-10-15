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

void M_SnmpRecv::getBreakerManagerOPNum(sObjData *obj,const QByteArray &data)
{
    obj->num = data.toDouble();
}

void M_SnmpRecv::devTypeData(int value, sDataPacket *pkt)
{
//    int line=3, loop=6;
//    if((value<5) || ((value>8) &&(value<13))) line = 1;

//    if(value < 5) loop = 2;
//    else if(value < 9) loop = 3;
//    else if(value < 13) loop = 4;

    //pkt->data.lineNum = 3;
    //pkt->data.loopNum = 0;

    int count = 0;
    for(int i=0 ; i<3 ; i++){
        if((&(mDataPacket->data.loop[i]))->num)
            count++;
    }
    if(count == 3)
        pkt->data.lineNum = pkt->data.loopNum = 3;
    else if(count < 3 && count > 0){
        pkt->data.loopNum = count;
        pkt->data.lineNum = 1;
    }
    pkt->devSpec = value;
}
