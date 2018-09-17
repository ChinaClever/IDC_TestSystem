#include "ip_snmpv1recv.h"

IP_SnmpV1Recv::IP_SnmpV1Recv()
{
    mPackets = IpDataPackets::bulid()->packets;
}

void IP_SnmpV1Recv::onResponseReceived(const QString &ip, const QByteArray &oid, const QByteArray &data)
{
    int ret = getMS(oid);
    if(ret) devData(data);
    else devInfo(data);
    sprintf(mDataPacket->ip, "%s",ip.toLatin1().data());
}

void IP_SnmpV1Recv::devInfo(const QByteArray &data)
{
    sprintf(mDataPacket->name, "%s",data.data());
}

void IP_SnmpV1Recv::devData(const QByteArray &data)
{
    sObjData *obj = mDataPacket->data.line;
    int id = getItemByOid(2);
    switch (id%11) {
    case 1: obj[0].vol.value = data.toInt(); break;
    case 2: obj[1].vol.value = data.toInt(); break;
    case 3: obj[2].vol.value = data.toInt(); break;

    case 4: obj[0].cur.value = data.toInt(); break;
    case 5: obj[1].cur.value = data.toInt(); break;
    case 6: obj[2].cur.value = data.toInt(); break;

    case 7: obj[0].ele = data.toInt(); break;
    case 8: obj[1].ele = data.toInt(); break;
    case 9: obj[2].ele = data.toInt(); break;

    case 10: mDataPacket->data.env.tem[0].value = data.toInt(); break;
    case 0: mDataPacket->data.env.hum[0].value = data.toInt(); break;
    default:         break;
    }
}

int IP_SnmpV1Recv::getMS(const QByteArray &oid)
{
    mOid = QString(oid).remove(MIB_OID_CLEVER).remove(IP_MIB_OID).simplified();
    int id = getItemByOid(1);
    if(id > 1) {
        id = getItemByOid(2);
        if(id < 12) id = 1;
        else if(id < 23) id = 2;
        else if(id < 34) id = 3;
        else if(id < 45) id = 4;
        else id = 5;
        mDataPacket = &(mPackets->dev[id]);
        mDataPacket->id = id;
    } else {
        id = 0;
        mDataPacket = &(mPackets->dev[1]);
    }
    mDataPacket->offLine = 10;

    return id;
}

int IP_SnmpV1Recv::getItemByOid(int id)
{
    QStringList list = mOid.split(".");
    return list.at(id+1).toInt();
}
