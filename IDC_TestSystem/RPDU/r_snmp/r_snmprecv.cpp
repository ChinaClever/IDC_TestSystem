#include "r_snmprecv.h"

R_SnmpRecv::R_SnmpRecv()
{
    //mRate = 10;
    mPackets = R_DataPackets::bulid()->packets;
}

void R_SnmpRecv::devTypeData(int value, sDataPacket *pkt)
{   //1-A:1 1-B:2 1-C:3 1-D:4
    //2-A:5 2-B:6 2-C:7 2-D:8
    //3-A:9 3-B:10 3-C:11 3-D:12
    //pkt->data.lineNum = 2;
    pkt->devSpec = value;
}

void R_SnmpRecv::onResponseReceived(const QString &ip, const QByteArray &oid, const QByteArray &data)
{
    getMS(oid);
    sprintf(mDataPacket->ip, "%s",ip.toLatin1().data());
    int item = getItemByOid(2);
    switch (item) {
    case 1: devInfo(data); break;

    default:  qDebug() << "R_SNMP_Recv::onResponseReceived" << item; break;
    }

}

void R_SnmpRecv::devInfo(const QByteArray &data)
{
    bool ok;
    int item = getItemByOid(3);
    switch (item) {
    case 1: sprintf(mDataPacket->name, "%s",data.data()); mDataPacket->txType = 1 ;break;
    case 2: {
        std::string str = data.toStdString();
        int value = (str == "A")?1:(str == "B"?2:(str == "C"?3:0));
        devTypeData(value , mDataPacket);
    }
        break;
    case 3: case 4: case 5:lineData(data);break;
    case 6: envData(data);break;
    case 7: mDataPacket->data.outputNum = data.toHex().toInt(&ok,16);break;
    case 8: case 9:case 10:case 11:case 12:case 13:case 19: case 20:outputInfo(data);break;
    default:
        break;
    }

}

void R_SnmpRecv::lineData(const QByteArray &data)
{
    sObjData *obj = NULL;
    bool ok;
    int index = getItemByOid(3);
    if(index >= 3 && index <= 5)
    {
        obj = &(mDataPacket->data.line[index-3]);
        int item = getItemByOid(4);
        switch (item) {
        case 1: obj->pow = data.toDouble();break;
        case 2: obj->pf = data.toDouble()*100 ;break;
        case 3: obj->ele = data.toDouble()*10 ;break;
        case 4: obj->cur.value = data.toDouble()*10 ;break;
        case 5: obj->vol.value = data.toHex().toInt(&ok,16) ;
            if(obj->vol.value) obj->sw=1; else obj->sw=0;break;

        case 6: obj->cur.min = data.toDouble() * 10 ;obj->cur.crMin = data.toDouble() * 10 ; break;
        case 7: obj->cur.max = data.toDouble() * 10; obj->cur.crMax = data.toDouble() * 10 ; break;

        case 8: obj->vol.min = data.toHex().toInt(&ok,16) ;obj->vol.crMin= data.toHex().toInt(&ok,16) ;/* qDebug()<<"snmp vol.min"<<obj->vol.min; */break;
        case 9: obj->vol.max = data.toHex().toInt(&ok,16) ;obj->vol.crMax= data.toHex().toInt(&ok,16) ; /*qDebug()<<"snmp vol.max"<<obj->vol.max;*/break;
        default:
            break;
        }
    }
}

void R_SnmpRecv::envData(const QByteArray &data)
{
    sEnvData *env = &(mDataPacket->data.env);

    bool ok;
    env->envNum = 4;
    int item = getItemByOid(4);
    switch (item) {
    case 1: env->tem[0].value = data.toHex().toInt(&ok,16); /*env->tem[0].min= 0 ; env->tem[0].max = 40 ;*/break;
    case 2: env->tem[1].value = data.toHex().toInt(&ok,16);/* env->tem[1].min = 0 ; env->tem[1].max = 40 ;*/break;
    case 3: env->tem[2].value = data.toHex().toInt(&ok,16); /*env->tem[2].min = 0 ; env->tem[2].max = 40 ;*/break;
    case 4: env->tem[3].value = data.toHex().toInt(&ok,16); /*env->tem[3].min = 0 ; env->tem[3].max = 40 ;*/break;

    case 5: env->hum[0].value = data.toHex().toInt(&ok,16) ; /*env->hum[0].min = 0 ;env->hum[0].max = 99 ;*/break;
    case 6: env->hum[1].value = data.toHex().toInt(&ok,16) ; /*env->hum[1].min = 0 ;env->hum[1].max = 99 ;*/break;
    case 7: env->hum[2].value = data.toHex().toInt(&ok,16) ; /*env->hum[2].min = 0 ;env->hum[2].max = 99 ;*/break;
    case 8: env->hum[3].value = data.toHex().toInt(&ok,16) ; /*env->hum[3].min = 0 ;env->hum[3].max = 99 ;*/break;

    case 9: env->door[0] = data.toStdString()=="None."?0:(data.toStdString()=="Closed."?1:2); break;
    case 10: env->door[1] = data.toStdString()=="None."?0:(data.toStdString()=="Closed."?1:2); break;
    case 11: env->smoke[0] = data.toStdString()=="None."?0:(data.toStdString()=="Normal."?1:2);break;
    case 12: env->water[0] = data.toStdString()=="None."?0:(data.toStdString()=="Normal."?1:2); break;

    default: qDebug() << "R_SNMP_Recv::envData" << item; break;
    }
}

void R_SnmpRecv::outputInfo(const QByteArray &data)
{
    int id = getItemByOid(4) - 1;
    sObjData *obj = &(mDataPacket->data.output[id]);
    int item = getItemByOid(3);
    if(id >= 0 && id < 24){
        switch(item){
        case 8:sprintf(obj->name, "%s", data.data());break;
        case 9:obj->sw = data.toStdString()=="OFF"?0:1;break;
        case 10:obj->cur.value = data.toDouble() * 10;break;
        case 11:obj->cur.min = obj->cur.crMin = data.toDouble() * 10;/*qDebug()<<"snmp cur.min"<<obj->cur.min;*/break;
        case 12:obj->cur.max = obj->cur.crMax = data.toDouble() * 10;/*qDebug()<<"snmp cur.max"<<obj->cur.max;*/break;
        case 13:obj->ele = data.toDouble()*10 ;break;
        }
    }
    switch (item) {
    case 19:envMinData(data);break;
    case 20:envMaxData(data);break;
    default:break;
    }
}

void R_SnmpRecv::envMinData(const QByteArray &data)
{
    sEnvData *env = &(mDataPacket->data.env);

    bool ok;
    int item = getItemByOid(4);
    switch(item)
    {
    case 1:env->tem[0].min = data.toHex().toInt(&ok,16); break;
    case 2:env->tem[1].min = data.toHex().toInt(&ok,16); break;
    case 3:env->tem[2].min = data.toHex().toInt(&ok,16); break;
    case 4:env->tem[3].min = data.toHex().toInt(&ok,16); break;
    case 5:env->hum[0].min = data.toHex().toInt(&ok,16); break;
    case 6:env->hum[1].min = data.toHex().toInt(&ok,16); break;
    case 7:env->hum[2].min = data.toHex().toInt(&ok,16); break;
    case 8:env->hum[3].min = data.toHex().toInt(&ok,16); break;
    default:break;
    }

}

void R_SnmpRecv::envMaxData(const QByteArray &data)
{
    sEnvData *env = &(mDataPacket->data.env);

    bool ok;
    int item = getItemByOid(4);
    switch(item)
    {
    case 1:env->tem[0].max = data.toHex().toInt(&ok,16); break;
    case 2:env->tem[1].max = data.toHex().toInt(&ok,16); break;
    case 3:env->tem[2].max = data.toHex().toInt(&ok,16); break;
    case 4:env->tem[3].max = data.toHex().toInt(&ok,16); break;
    case 5:env->hum[0].max = data.toHex().toInt(&ok,16); break;
    case 6:env->hum[1].max = data.toHex().toInt(&ok,16); break;
    case 7:env->hum[2].max = data.toHex().toInt(&ok,16); break;
    case 8:env->hum[3].max = data.toHex().toInt(&ok,16); break;
    default:break;
    }
}
