/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "snmp_zmrecv.h"

enum Endian
{
    LittileEndian,
    BigEndian
};

int byteAraryToInt(QByteArray arr,  Endian endian = BigEndian)
{
    if (arr.size() < 4)
        return 0;

    int res = 0;

    // 小端模式
    if (endian == LittileEndian)
    {
        res = arr.at(0) & 0x000000FF;
        res |= (arr.at(1) << 8) & 0x0000FF00;
        res |= (arr.at(2) << 16) & 0x00FF0000;
        res |= (arr.at(3) << 24) & 0xFF000000;
    }

    // 大端模式
    else if (endian == BigEndian)
    {
        res = (arr.at(0) << 24) & 0xFF000000;
        res |= (arr.at(1) << 16) & 0x00FF0000;
        res |= arr.at(2) << 8 & 0x0000FF00;
        res |= arr.at(3) & 0x000000FF;
    }
    return res;
}

SNMP_ZmRecv::SNMP_ZmRecv()
{

}


void SNMP_ZmRecv::onResponseReceived(const QString &ip, const QByteArray &oid, const QByteArray &data)
{
    getMS(oid);
    sprintf(mDataPacket->ip, "%s",ip.toLatin1().data());
    int item = getItemByOid(2);
    switch (item) {
    case 1: devInfo(data); break;
    case 2: lineData(data); break;
    case 3: lineData(data); break;
    case 4: envData(data); break;

    case 5: case 6: case 7:  case 9:
    case 10: outputData(data); break;
    case 8: outputCur(data); break;

    default:  qDebug() << "SNMP_ZmRecv::onResponseReceived" << item; break;
    }

}

void SNMP_ZmRecv::outputData(const QByteArray &data)
{
    int id = getItemByOid(3) - 1;
    sObjData *obj = &(mDataPacket->data.output[id]);

    int item = getItemByOid(2);
    switch (item) {
    case 5:  sprintf(obj->name, "%s", data.data());; break;
    case 6:  obj->delay = byteAraryToInt(data) ; break;
    case 7:  obj->sw = byteAraryToInt(data) ; break;
    case 9:  obj->pf = byteAraryToInt(data) ; break;
    case 10:  obj->ele = byteAraryToInt(data) ; break;
     default: qDebug() << "SNMP_ZmRecv::outputData" << item; break;
    }

}

void SNMP_ZmRecv::outputCur(const QByteArray &data)
{
    int id = getItemByOid(4) - 1;
    sObjData *obj = &(mDataPacket->data.output[id]);

    int item = getItemByOid(3);
    switch (item) {
    case 1: obj->cur.value = byteAraryToInt(data) / 10; break;
    case 2: obj->cur.min = byteAraryToInt(data) / 10 ; break;
    case 3: obj->cur.crMin = byteAraryToInt(data) / 10; break;
    case 4: obj->cur.crMax = byteAraryToInt(data) / 10 ; break;
    case 5: obj->cur.max = byteAraryToInt(data) / 10; break;
    default: qDebug() << "SNMP_ZmRecv::outputCur" << item; break;
    }
}

void SNMP_ZmRecv::envData(const QByteArray &data)
{
    sEnvData *env = &(mDataPacket->data.env);

    int item = getItemByOid(3);
    switch (item) {
    case 1: env->tem[0].value = byteAraryToInt(data) / 10; break;
    case 2: env->tem[1].value = byteAraryToInt(data) / 10; break;
    case 3: env->hum[0].value = byteAraryToInt(data) / 10; break;
    case 4: env->hum[1].value = byteAraryToInt(data) / 10; break;

    case 5: env->door[0] = byteAraryToInt(data) ; break;
    case 6: env->door[1] = byteAraryToInt(data) ; break;
    case 7: env->smoke[0] = byteAraryToInt(data) ; break;
    case 8: env->water[0] = byteAraryToInt(data) ; break;

    case 9: env->tem[0].min = byteAraryToInt(data) / 10 ; break;
    case 10: env->tem[0].crMin = byteAraryToInt(data) / 10; break;
    case 11: env->tem[0].crMax = byteAraryToInt(data) / 10 ; break;
    case 12: env->tem[0].max = byteAraryToInt(data) / 10; break;

    case 13: env->tem[1].min = byteAraryToInt(data) / 10 ; break;
    case 14: env->tem[1].crMin = byteAraryToInt(data) / 10; break;
    case 15: env->tem[1].crMax = byteAraryToInt(data) / 10 ; break;
    case 16: env->tem[1].max = byteAraryToInt(data) / 10; break;

    case 17: env->hum[0].min = byteAraryToInt(data) / 10 ; break;
    case 18: env->hum[0].crMin = byteAraryToInt(data) / 10; break;
    case 19: env->hum[0].crMax = byteAraryToInt(data) / 10 ; break;
    case 20: env->hum[0].max = byteAraryToInt(data) / 10; break;

    case 21: env->hum[1].min = byteAraryToInt(data) / 10 ; break;
    case 22: env->hum[1].crMin = byteAraryToInt(data) / 10; break;
    case 23: env->hum[1].crMax = byteAraryToInt(data) / 10 ; break;
    case 24: env->hum[1].max = byteAraryToInt(data) / 10; break;

    default: qDebug() << "SNMP_ZmRecv::envData" << item; break;
    }
}

void SNMP_ZmRecv::lineData(const QByteArray &data)
{
    int id = getItemByOid(3) - 1;
    sObjData *obj = &(mDataPacket->data.line[id]);

    int item = getItemByOid(4);
    switch (item) {
    case 1: obj->cur.value = byteAraryToInt(data) / 10; break;
    case 2: obj->vol.value = byteAraryToInt(data) / 10; if(obj->vol.value) obj->sw=1; else obj->sw=0; break;
    case 3: obj->pow = byteAraryToInt(data) / 10; break;
    case 4: obj->pf = byteAraryToInt(data) ; break;
    case 5: obj->ele = byteAraryToInt(data) ; break;

    case 6: obj->cur.min = byteAraryToInt(data) / 10 ; break;
    case 7: obj->cur.crMin = byteAraryToInt(data) / 10; break;
    case 8: obj->cur.crMax = byteAraryToInt(data) / 10 ; break;
    case 9: obj->cur.max = byteAraryToInt(data) / 10; break;

    case 10: obj->vol.min = byteAraryToInt(data) / 10 ; break;
    case 11: obj->vol.crMin = byteAraryToInt(data) / 10; break;
    case 12: obj->vol.crMax = byteAraryToInt(data) / 10 ; break;
    case 13: obj->vol.max = byteAraryToInt(data) / 10; break;
    default: qDebug() << "SNMP_ZmRecv::lineData" << item; break;
    }

}

void SNMP_ZmRecv::loopData(const QByteArray &data)
{
    int id = getItemByOid(3) - 1;
    sObjData *obj = &(mDataPacket->data.loop[id]);

    int item = getItemByOid(4);
    switch (item) {
    case 1: obj->sw = byteAraryToInt(data); break;
    case 2:                         break;
    case 3: obj->cur.value = byteAraryToInt(data) / 10; break;
    case 4: obj->vol.value = byteAraryToInt(data) / 10; break;
    case 5: obj->ele = byteAraryToInt(data) ; break;
    case 6: obj->activePow = byteAraryToInt(data) / 10; break;

    case 7: obj->cur.min = byteAraryToInt(data) / 10 ; break;
    case 8: obj->cur.crMin = byteAraryToInt(data) / 10; break;
    case 9: obj->cur.crMax = byteAraryToInt(data) / 10 ; break;
    case 10: obj->cur.max = byteAraryToInt(data) / 10; break;
    default: qDebug() << "SNMP_ZmRecv::loopData" << item; break;
    }
}



void SNMP_ZmRecv::devInfo(const QByteArray &data)
{
    int item = getItemByOid(3);
    switch (item) {
    case 1: sprintf(mDataPacket->name, "%s",data.data()); break;
    case 2: devTypeData(byteAraryToInt(data), mDataPacket);  break;
    case 3: mDataPacket->data.outputNum = byteAraryToInt(data); break;
    case 4: sprintf(mDataPacket->mac, "%s",data.data()); break;
    case 5: sprintf(mDataPacket->versionStr, "%s",data.data()); break;
    case 6: mDataPacket->hz = byteAraryToInt(data); break;
    default:
        break;
    }
}

void SNMP_ZmRecv::getMS(const QByteArray &oid)
{
    mOid = QString(oid).remove(MIB_OID_CLEVER).simplified();
    int id = getItemByOid(1);
    if(id >= 0) {
        mDataPacket = &(mPackets->dev[id]);
        mDataPacket->id = id;
        mDataPacket->offLine = 10;
    }
}

int SNMP_ZmRecv::getItemByOid(int id)
{
    QStringList list = mOid.split(".");
    return list.at(id+1).toInt();
}
