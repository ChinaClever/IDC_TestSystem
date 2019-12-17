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
    obj->num = data.toDouble();
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
    pkt->devSpec = value;
}

void MV1_SnmpRecv::onResponseReceived(const QString &ip, const QByteArray &oid, const QByteArray &data)
{
    getMS(oid);
    sprintf(mDataPacket->ip, "%s",ip.toLatin1().data());
    int item = getItemByOid(2);
    switch (item) {
    case 1: devInfo(data); break;

    default:  qDebug() << "MV1_SnmpRecv::onResponseReceived" << item; break;
    }
}

void MV1_SnmpRecv::devInfo(const QByteArray &data)
{
    bool ok;
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
    }
        break;
    case 2:{
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
    case 3: case 4: case 5: lineData(data);break;
    case 6: envData(data);break;
    case 7: mDataPacket->data.outputNum = data.toHex().toInt(&ok,16);break;
    case 8: case 9:case 10:case 11:case 12:case 13:outputInfo(data);break;
    default:
        break;
    }
}

void MV1_SnmpRecv::lineData(const QByteArray &data)
{
    bool ok;
    int id = getItemByOid(3) - 3;
    sObjData *obj = &(mDataPacket->data.line[id]);

    int item = getItemByOid(4);
    switch (item) {
    case 1: obj->pow = data.toDouble()*1000;break;
    case 2: obj->pf = data.toDouble()*100 ; break;
    case 3: obj->ele = data.toDouble()*10 ; break;
    case 4: obj->cur.value = data.toDouble() * 10;break;
    case 5: obj->vol.value = data.toHex().toInt(&ok,16);break;
    case 6: obj->cur.min = data.toDouble() * 10; break;
    case 7: obj->cur.max = data.toDouble() * 10; break;

    case 8: obj->vol.min = data.toHex().toInt(&ok,16); break;
    case 9: obj->vol.max = data.toHex().toInt(&ok,16); break;
    default: qDebug() << "MV1_SnmpRecv::lineData" << item; break;
    }
}

void MV1_SnmpRecv::outputInfo(const QByteArray &data)
{
    int id = getItemByOid(4) - 1;
    sObjData *obj = &(mDataPacket->data.output[id]);
    int item = getItemByOid(3);
    if(id >= 0 && id < 24){
        switch(item){
        case 8:sprintf(obj->name, "%s", data.data());break;
        case 9:obj->sw = data.toStdString()=="OFF"?0:1;break;
        case 10:obj->cur.value = data.toDouble() * 10;break;
        case 11:obj->cur.min = obj->cur.crMin = data.toDouble() * 10;/*qDebug()<<"snmp cur.min"<<id<<obj->cur.min;*/break;
        case 12:obj->cur.max = obj->cur.crMax = data.toDouble() * 10;/*qDebug()<<"snmp cur.max"<<id<<obj->cur.max;*/break;
        case 13:obj->ele = data.toDouble()*10 ;break;
        default: qDebug() << "MV1_SnmpRecv::outputInfo" << item; break;
        }
    }
}

void MV1_SnmpRecv::envData(const QByteArray &data)
{
    sEnvData *env = &(mDataPacket->data.env);

    bool ok;
    env->envNum = 2;
    int item = getItemByOid(4);
    switch (item) {
    case 1: env->tem[0].value = data.toHex().toInt(&ok,16); env->tem[0].min= 0 ; env->tem[0].max = 40 ;break;
    case 2: env->tem[1].value = data.toHex().toInt(&ok,16); env->tem[1].min= 0 ; env->tem[1].max = 40 ;break;
    case 3: env->tem[2].value = data.toHex().toInt(&ok,16); /*env->tem[2].min = 0 ; env->tem[2].max = 40 ;*/break;
    case 4: env->tem[3].value = data.toHex().toInt(&ok,16); /*env->tem[3].min = 0 ; env->tem[3].max = 40 ;*/break;

    case 5: env->hum[0].value = data.toHex().toInt(&ok,16) ; env->hum[0].min = 0 ;env->hum[0].max = 99 ;break;
    case 6: env->hum[1].value = data.toHex().toInt(&ok,16) ; env->hum[1].min = 0 ;env->hum[1].max = 99 ;break;
    case 7: env->hum[2].value = data.toHex().toInt(&ok,16) ; /*env->hum[2].min = 0 ;env->hum[2].max = 99 ;*/break;
    case 8: env->hum[3].value = data.toHex().toInt(&ok,16) ; /*env->hum[3].min = 0 ;env->hum[3].max = 99 ;*/break;

    case 9: env->door[0] = data.toStdString()=="None."|| data.toStdString()=="NULL"?0:(data.toStdString()=="Closed."?1:2); break;
    case 10: env->door[1] = data.toStdString()=="None."|| data.toStdString()=="NULL"?0:(data.toStdString()=="Closed."?1:2); break;
    case 11: env->smoke[0] = data.toStdString()=="None."|| data.toStdString()=="NULL"?0:(data.toStdString()=="Normal."?1:2);break;
    case 12: env->water[0] = data.toStdString()=="None."|| data.toStdString()=="NULL"?0:(data.toStdString()=="Normal."?1:2);break;

    default: qDebug() << "MV1_SnmpRecv::envData" << item; break;
    }
}
