#include "z_snmprecv.h"

Z_SnmpRecv::Z_SnmpRecv()
{
    mRate = 10;
    mPackets = Z_DataPackets::bulid()->packets;
}

void Z_SnmpRecv::getBreakerManagerOPNum(sObjData *obj,const QByteArray &data)
{
    char string[64];
    sprintf(string, "%s", data.data());
    QString str(string);
    QStringList strlist = str.split("-");
    if(strlist.size() == 2)
        obj->num =strlist.at(1).toInt()-strlist.at(0).toInt()+1;
    else
        obj->num = 0;
}

void Z_SnmpRecv::devTypeData(int value, sDataPacket *pkt)
{
//    int line=3, loop=6;
//    if((value<5) || ((value>8) &&(value<13))) line = 1;

//    if(value < 5) loop = 2;
//    else if(value < 9) loop = 3;
//    else if(value < 13) loop = 4;

//    pkt->data.lineNum = line;
//    pkt->data.loopNum = loop;
//    pkt->devSpec = value%4;
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
