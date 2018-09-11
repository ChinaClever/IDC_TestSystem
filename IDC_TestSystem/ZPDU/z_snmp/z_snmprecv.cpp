#include "z_snmprecv.h"

Z_SnmpRecv::Z_SnmpRecv()
{

}

void Z_SnmpRecv::onResponseReceived(const QString &ip, const QByteArray &oid, const QByteArray &data)
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

    default:  qDebug() << "Z_SnmpRecv::onResponseReceived" << item; break;
    }

}

void Z_SnmpRecv::outputData(const QByteArray &data)
{
    int id = getItemByOid(3) - 1;
    sObjData *obj = &(mDataPacket->data.output[id]);

    int item = getItemByOid(2);
    switch (item) {
    case 5:  sprintf(obj->name, "%s", data.data());; break;
    case 6:  obj->delay = data.toInt() ; break;
    case 7:  obj->sw = data.toInt() ; break;
    case 9:  obj->pf = data.toInt() ; break;
    case 10:  obj->ele = data.toInt() ; break;
     default: qDebug() << "Z_SnmpRecv::outputData" << item; break;
    }

}

void Z_SnmpRecv::outputCur(const QByteArray &data)
{
    int id = getItemByOid(4) - 1;
    sObjData *obj = &(mDataPacket->data.output[id]);

    int item = getItemByOid(3);
    switch (item) {
    case 1: obj->cur.value = data.toInt() / 10; break;
    case 2: obj->cur.min = data.toInt() / 10 ; break;
    case 3: obj->cur.crMin = data.toInt() / 10; break;
    case 4: obj->cur.crMax = data.toInt() / 10 ; break;
    case 5: obj->cur.max = data.toInt() / 10; break;
    default: qDebug() << "Z_SnmpRecv::outputCur" << item; break;
    }
}

void Z_SnmpRecv::envData(const QByteArray &data)
{
    sEnvData *env = &(mDataPacket->data.env);

    int item = getItemByOid(3);
    switch (item) {
    case 1: env->tem[0].value = data.toInt() / 10; break;
    case 2: env->tem[1].value = data.toInt() / 10; break;
    case 3: env->hum[0].value = data.toInt() / 10; break;
    case 4: env->hum[1].value = data.toInt() / 10; break;

    case 5: env->door[0] = data.toInt() ; break;
    case 6: env->door[1] = data.toInt() ; break;
    case 7: env->smoke[0] = data.toInt() ; break;
    case 8: env->water[0] = data.toInt() ; break;

    case 9: env->tem[0].min = data.toInt() / 10 ; break;
    case 10: env->tem[0].crMin = data.toInt() / 10; break;
    case 11: env->tem[0].crMax = data.toInt() / 10 ; break;
    case 12: env->tem[0].max = data.toInt() / 10; break;

    case 13: env->tem[1].min = data.toInt() / 10 ; break;
    case 14: env->tem[1].crMin = data.toInt() / 10; break;
    case 15: env->tem[1].crMax = data.toInt() / 10 ; break;
    case 16: env->tem[1].max = data.toInt() / 10; break;

    case 17: env->hum[0].min = data.toInt() / 10 ; break;
    case 18: env->hum[0].crMin = data.toInt() / 10; break;
    case 19: env->hum[0].crMax = data.toInt() / 10 ; break;
    case 20: env->hum[0].max = data.toInt() / 10; break;

    case 21: env->hum[1].min = data.toInt() / 10 ; break;
    case 22: env->hum[1].crMin = data.toInt() / 10; break;
    case 23: env->hum[1].crMax = data.toInt() / 10 ; break;
    case 24: env->hum[1].max = data.toInt() / 10; break;

    default: qDebug() << "Z_SnmpRecv::envData" << item; break;
    }
}

void Z_SnmpRecv::lineData(const QByteArray &data)
{
    int id = getItemByOid(3) - 1;
    sObjData *obj = &(mDataPacket->data.line[id]);

    int item = getItemByOid(4);
    switch (item) {
    case 1: obj->cur.value = data.toInt() / 10; break;
    case 2: obj->vol.value = data.toInt() / 10; if(obj->vol.value) obj->sw=1; else obj->sw=0; break;
    case 3: obj->pow = data.toInt() / 10; break;
    case 4: obj->pf = data.toInt() ; break;
    case 5: obj->ele = data.toInt() ; break;

    case 6: obj->cur.min = data.toInt() / 10 ; break;
    case 7: obj->cur.crMin = data.toInt() / 10; break;
    case 8: obj->cur.crMax = data.toInt() / 10 ; break;
    case 9: obj->cur.max = data.toInt() / 10; break;

    case 10: obj->vol.min = data.toInt() / 10 ; break;
    case 11: obj->vol.crMin = data.toInt() / 10; break;
    case 12: obj->vol.crMax = data.toInt() / 10 ; break;
    case 13: obj->vol.max = data.toInt() / 10; break;
    default: qDebug() << "Z_SnmpRecv::lineData" << item; break;
    }

}

void Z_SnmpRecv::loopData(const QByteArray &data)
{
    int id = getItemByOid(3) - 1;
    sObjData *obj = &(mDataPacket->data.loop[id]);

    int item = getItemByOid(4);
    switch (item) {
    case 1: obj->sw = data.toInt(); break;
    case 2:                         break;
    case 3: obj->cur.value = data.toInt() / 10; break;
    case 4: obj->vol.value = data.toInt() / 10; break;
    case 5: obj->ele = data.toInt() ; break;
    case 6: obj->activePow = data.toInt() / 10; break;

    case 7: obj->cur.min = data.toInt() / 10 ; break;
    case 8: obj->cur.crMin = data.toInt() / 10; break;
    case 9: obj->cur.crMax = data.toInt() / 10 ; break;
    case 10: obj->cur.max = data.toInt() / 10; break;
    default: qDebug() << "Z_SnmpRecv::loopData" << item; break;
    }
}

void Z_SnmpRecv::devTypeData(int value, sDataPacket *pkt)
{
    int line=3, loop=6;
    if((value<5) || ((value>8) &&(value<13))) line = 1;

    if(value < 5) loop = 2;
    else if(value < 9) loop = 3;
    else if(value < 13) loop = 4;

    pkt->data.lineNum = line;
    pkt->data.loopNum = loop;
    pkt->devSpec = value%4;
}

void Z_SnmpRecv::devInfo(const QByteArray &data)
{
    int item = getItemByOid(3);
    switch (item) {
    case 1: sprintf(mDataPacket->name, "%s",data.data()); break;
    case 2: devTypeData(data.toInt(), mDataPacket);  break;
    case 3: mDataPacket->data.outputNum = data.toInt();  break;
    case 4: sprintf(mDataPacket->mac, "%s",data.data()); break;
    case 5: sprintf(mDataPacket->versionStr, "%s",data.data()); break;
    case 6: mDataPacket->hz = data.toInt(); break;
    default:
        break;
    }
}

void Z_SnmpRecv::getMS(const QByteArray &oid)
{
    mOid = QString(oid).remove(MIB_OID_CLEVER);
    int id = getItemByOid(1);
    if(id >= 0) {
        mDataPacket = Z_DataPackets::bulid()->getDev(id);
        mDataPacket->offLine = 7;
    }
}

int Z_SnmpRecv::getItemByOid(int id)
{
    QStringList list = mOid.split(".");
    return list.at(id).toInt();
}
