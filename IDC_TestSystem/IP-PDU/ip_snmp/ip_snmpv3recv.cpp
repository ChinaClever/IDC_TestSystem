#include "ip_snmpv3recv.h"

IP_SnmpV3Recv::IP_SnmpV3Recv()
{
    mPackets = IpDataPackets::bulid()->packets;
}

void IP_SnmpV3Recv::onResponseReceived(const QString &ip, const QByteArray &oid, const QByteArray &data)
{
    bool ret = getMS(oid);
    int id = getItemByOid(1);
    switch(id)
    {
        case 1:devInfo(data); break;
        case 2:devData(data); break;
    }
    sprintf(mDataPacket->ip, "%s",ip.toLatin1().data());
}


void IP_SnmpV3Recv::devData(const QByteArray &data)
{
    bool ok;
    sObjData *obj = mDataPacket->data.line;
    int id = getItemByOid(2);
    switch (id) {
    case 1: obj[0].vol.value = data.toHex().toInt(&ok,16);break;
    case 2: obj[1].vol.value = data.toHex().toInt(&ok,16); break;
    case 3: obj[2].vol.value = data.toHex().toInt(&ok,16); break;

    case 4: obj[0].cur.value = data.toHex().toInt(&ok,16); break;
    case 5: obj[1].cur.value = data.toHex().toInt(&ok,16); break;
    case 6: obj[2].cur.value = data.toHex().toInt(&ok,16); break;

    case 7: obj[0].pf = data.toHex().toInt(&ok,16); break;
    case 8: obj[1].pf = data.toHex().toInt(&ok,16); break;
    case 9: obj[2].pf = data.toHex().toInt(&ok,16); break;

    case 10: obj[0].pow = data.toHex().toInt(&ok,16); break;
    case 11: obj[1].pow = data.toHex().toInt(&ok,16); break;
    case 12: obj[2].pow = data.toHex().toInt(&ok,16); break;

    case 13: obj[0].activePow = data.toHex().toInt(&ok,16); break;
    case 14: obj[1].activePow = data.toHex().toInt(&ok,16); break;
    case 15: obj[2].activePow = data.toHex().toInt(&ok,16); break;

    case 16: obj[0].ele = data.toHex().toInt(&ok,16); break;
    case 17: obj[1].ele = data.toHex().toInt(&ok,16); break;
    case 18: obj[2].ele = data.toHex().toInt(&ok,16); break;

    case 19: obj[0].sw = data.toHex().toInt(&ok,16)==2?1:0; break;
    case 20: obj[1].sw = data.toHex().toInt(&ok,16)==2?1:0; break;
    case 21: obj[2].sw = data.toHex().toInt(&ok,16)==2?1:0; break;

    case 22: mDataPacket->hz = data.toHex().toInt(&ok,16); break;
    case 23: mDataPacket->data.env.tem[0].value = data.toHex().toInt(&ok,16); break;
    case 24: mDataPacket->data.env.hum[0].value = data.toHex().toInt(&ok,16); break;
    default:         break;
    }
}

void IP_SnmpV3Recv::devInfo(const QByteArray &data)
{
    bool ok;
    int id = getItemByOid(2);
    switch (id) {
    case 1: sprintf(mDataPacket->name, "%s",data.data()); break;
    case 2:  break;
    case 3: mDataPacket->br = data.toHex().toInt(&ok,16); break;
    case 4: mDataPacket->data.lineNum = data.toHex().toInt(&ok,16); break;
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
