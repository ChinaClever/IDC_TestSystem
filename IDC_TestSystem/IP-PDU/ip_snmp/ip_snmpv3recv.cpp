#include "ip_snmpv3recv.h"

IP_SnmpV3Recv::IP_SnmpV3Recv()
{
    mPackets = IpDataPackets::bulid()->packets;
}

void IP_SnmpV3Recv::onResponseReceived(const QString &ip, const QByteArray &oid, const QByteArray &data)
{
    bool ret = getMS(oid);
    if(ret) devData(data);
    else devInfo(data);
    sprintf(mDataPacket->ip, "%s",ip.toLatin1().data());
}


void IP_SnmpV3Recv::devData(const QByteArray &data)
{
    sObjData *obj = mDataPacket->data.line;
    int id = getItemByOid(2);
    switch (id) {
    case 1: obj[0].vol.value = data.toInt(); break;
    case 2: obj[1].vol.value = data.toInt(); break;
    case 3: obj[2].vol.value = data.toInt(); break;

    case 4: obj[0].cur.value = data.toInt(); break;
    case 5: obj[1].cur.value = data.toInt(); break;
    case 6: obj[2].cur.value = data.toInt(); break;

    case 7: obj[0].pf = data.toInt(); break;
    case 8: obj[1].pf = data.toInt(); break;
    case 9: obj[2].pf = data.toInt(); break;

    case 10: obj[0].pow = data.toInt(); break;
    case 11: obj[1].pow = data.toInt(); break;
    case 12: obj[2].pow = data.toInt(); break;

    case 13: obj[0].activePow = data.toInt(); break;
    case 14: obj[1].activePow = data.toInt(); break;
    case 15: obj[2].activePow = data.toInt(); break;

    case 16: obj[0].ele = data.toInt(); break;
    case 17: obj[1].ele = data.toInt(); break;
    case 18: obj[2].ele = data.toInt(); break;

    case 19: obj[0].sw = data.toInt(); break;
    case 20: obj[1].sw = data.toInt(); break;
    case 21: obj[2].sw = data.toInt(); break;

    case 22: mDataPacket->hz = data.toInt(); break;
    case 23: mDataPacket->data.env.tem[0].value = data.toInt(); break;
    case 24: mDataPacket->data.env.hum[0].value = data.toInt(); break;
    default:         break;
    }
}

void IP_SnmpV3Recv::devInfo(const QByteArray &data)
{
    int id = getItemByOid(2);
    switch (id) {
    case 1: sprintf(mDataPacket->name, "%s",data.data()); break;
    case 2:  break;
    case 3: mDataPacket->br = data.toInt(); break;
    case 4: mDataPacket->data.lineNum = data.toInt(); break;
    }

}


bool IP_SnmpV3Recv::getMS(const QByteArray &oid)
{
    bool ret = true;
    mOid = QString(oid).remove(MIB_OID_CLEVER).remove(IP_MIB_OID).simplified();
    int id = getItemByOid(1);
    if(id > 1) {
        id--;
    } else {
        ret = false;
    }

    mDataPacket = &(mPackets->dev[id]);
    mDataPacket->id = id;
    mDataPacket->offLine = 10;

    return ret;
}

int IP_SnmpV3Recv::getItemByOid(int id)
{
    QStringList list = mOid.split(".");
    return list.at(id+1).toInt();
}
