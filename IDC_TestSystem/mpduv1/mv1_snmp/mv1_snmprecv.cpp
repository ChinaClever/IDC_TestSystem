/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1_snmprecv.h"

MV1_SnmpRecv::MV1_SnmpRecv()
{
    mRate = 1;
    mPackets = MV1_DataPackets::bulid()->packets;
}

void MV1_SnmpRecv::getBreakerManagerOPNum(sObjData *obj,const QByteArray &data)
{
}

void MV1_SnmpRecv::getMS(const QByteArray &oid)
{
    mOid = QString(oid).remove(MIB_OID_CLEVER).simplified();
    int id = getItemByOid(2);
    if(id>=1&&id<=8){
        mDataPacket = &(mPackets->dev[1]);
        mDataPacket->id = 1;
        mDataPacket->offLine = 10;
    }
    else if(id>=9&&id<=15){
        mDataPacket = &(mPackets->dev[2]);
        mDataPacket->id = 2;
        mDataPacket->offLine = 10;
    }
    else if(id>=16&&id<=22){
        mDataPacket = &(mPackets->dev[3]);
        mDataPacket->id = 3;
        mDataPacket->offLine = 10;
    }
    if(id>=23&&id<=29){
        mDataPacket = &(mPackets->dev[4]);
        mDataPacket->id = 4;
        mDataPacket->offLine = 10;
    }
}

void MV1_SnmpRecv::devTypeData(int value, sDataPacket *pkt)
{
//    int count = 0;
//    for(int i=0 ; i<3 ; i++){
//        if((&(mDataPacket->data.loop[i]))->num)
//            count++;
//    }
//    if(count == 3)
//        pkt->data.lineNum = pkt->data.loopNum = 3;
//    else if(count < 3 && count > 0){
//        pkt->data.loopNum = count;
//        pkt->data.lineNum = 1;
//    }
    pkt->data.loopNum = mcountLoopNum.size();
    pkt->devSpec = value;
}

void MV1_SnmpRecv::onResponseReceived(const QString &ip, const QByteArray &oid, const QByteArray &data)
{
    getMS(oid);
    sprintf(mDataPacket->ip, "%s",ip.toLatin1().data());
    int item = getItemByOid(2);
    switch (item) {
    case 1: devInfo(data);break;
    case 2: lineData(data);break;
    case 3: envData(data);break;
    case 4:case 5:case 6:case 7:case 8: outputInfo(data);break;
//    case 9: lineData(data);break;
//    case 10: envData(data);break;
//    case 11:case 12:case 13:case 14:case 15: outputInfo(data);break;
//    case 16: lineData(data);break;
//    case 17: envData(data);break;
//    case 18:case 19:case 20:case 21:case 22: outputInfo(data);break;
//    case 23: lineData(data);break;
//    case 24: envData(data);break;
//    case 25:case 26:case 27:case 28:case 29: outputInfo(data);break;

    default:  qDebug() << "MV1_SnmpRecv::onResponseReceived" << item; break;
    }
}

void MV1_SnmpRecv::devInfo(const QByteArray &data)
{
    int item = getItemByOid(3);
    static int count1 = 0;
    static int count2 = 0; //防止第二次判断回路时，用上一次的数据
    switch (item) {
    case 1:{
        sprintf(mDataPacket->name, "%s",data.data());
        if(count1 == 1){
            mDataPacket->txType |= 0x01;
            count1 = 0;
        }
        else count1++;
        break;
    }

    case 3:{
        char string[64];
        sprintf(string, "%s", data.data());
        QString str(string);
        int value = (str == "A type"||str == "A")?1:(str == "B type"||str == "B"?2:(str == "C type"||str == "C"?3:0));
        if(count2 == 1)
        {
            devTypeData(value, mDataPacket);
            count2 = 0;
        }
        else count2++;
        break;
    }
    default:
        break;
    }
}

void MV1_SnmpRecv::lineData(const QByteArray &data)
{
    bool ok;
    int id = (getItemByOid(3)-1)%3;
    sObjData *obj = &(mDataPacket->data.line[id]);
    int item = getItemByOid(3);
    switch (item) {
    case 1: case 2:case 3:{obj->vol.value = data.toHex().toInt(&ok,16);}break;
    case 4: case 5:case 6:{obj->cur.value = data.toHex().toInt(&ok,16);}break;
    case 7: case 8:case 9:obj->pf = data.toHex().toInt(&ok,16) ;break;
    case 10: case 11:case 12:obj->pow = data.toHex().toInt(&ok,16);break;
    case 13: case 14:case 15:obj->ele = data.toHex().toInt(&ok,16) ;break;
    case 16: case 17:case 18:
    {
        obj->sw = data.toHex().toInt(&ok,16)==1?0:1;
        if(mcountLoopNum.count()>3) mcountLoopNum.clear();
        if(data.toHex().toInt(&ok,16)!=0)
        mcountLoopNum.insert(item,data.toHex().toInt(&ok,16));
    }
        break;
    default: qDebug() << "MV1_SnmpRecv::lineData" << item; break;
    }
}

void MV1_SnmpRecv::outputInfo(const QByteArray &data)
{
    bool ok;
    int id = getItemByOid(3) - 1;
    sObjData *obj = &(mDataPacket->data.output[id]);
    int item = getItemByOid(2);
    if(id >= 0 && id < 24){
        switch(item){
        case 4:obj->cur.value = data.toHex().toInt(&ok,16);break;
        case 5:obj->pf = data.toHex().toInt(&ok,16);break;
        case 6:obj->pow = data.toHex().toInt(&ok,16);break;
        case 7:obj->ele = data.toHex().toInt(&ok,16);break;
        case 8:obj->sw  = data.toStdString()=="OFF"?0:1;break;
        default: qDebug() << "MV1_SnmpRecv::outputInfo" << item; break;
        }
    }
}

void MV1_SnmpRecv::envData(const QByteArray &data)
{
    sEnvData *env = &(mDataPacket->data.env);

    bool ok;
    env->envNum = 2;
    int item = getItemByOid(3);
    switch (item) {
    case 1: {env->tem[0].value = data.toHex().toInt(&ok,16); env->tem[0].min= 0 ; env->tem[0].max = 40 ;}break;
    case 2: {env->tem[1].value = data.toHex().toInt(&ok,16); env->tem[1].min= 0 ; env->tem[1].max = 40 ;}break;

    case 3: {env->hum[0].value = data.toHex().toInt(&ok,16) ; env->hum[0].min = 0 ;env->hum[0].max = 99 ;}break;
    case 4: {env->hum[1].value = data.toHex().toInt(&ok,16) ; env->hum[1].min = 0 ;env->hum[1].max = 99 ;}break;


    default: qDebug() << "MV1_SnmpRecv::envData" << item; break;
    }
}
