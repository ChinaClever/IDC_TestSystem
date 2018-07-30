/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ip_buildjson.h"

IP_BuildJson::IP_BuildJson()
{

}

IP_BuildJson *IP_BuildJson::bulid()
{
    static IP_BuildJson* sington = nullptr;
    if(sington == nullptr)
        sington = new IP_BuildJson();
    return sington;
}

bool IP_BuildJson::getJson(IpDevPacket *packet, QJsonObject &json)
{
    bool ret = true;

    if(packet->rtuData.offLine > 0) {
        head(packet, json);
        devData(packet, json);
        //  pduNetData(packet->net, json);
    } else {
        ret = false;
    }

    return ret;
}

bool IP_BuildJson::saveJson(const QString &name, QJsonObject &json)
{
    QJsonDocument jsonDoc(json);
    QByteArray ba = jsonDoc.toJson();
    QFile file("F:/" + name+".json");
    bool ret = file.open(QIODevice::WriteOnly);
    if(ret) {
        file.write(ba);
        file.close();
    } else {
        qDebug() << "ip write json file failed";
    }

    return ret;
}

void IP_BuildJson::head(IpDevPacket *packet,QJsonObject &obj)
{
    obj.insert("company", "CLEVER");
    obj.insert("version", 1);

    uutInfo(packet, obj);
    ateInfo(packet, obj);
}

void IP_BuildJson::uutInfo(IpDevPacket *packet, QJsonObject &json)
{
    QJsonObject obj;
    obj.insert("url", "www.clever.com");
    obj.insert("idc", "idc_test"); //

    obj.insert("room", "room_test");
    obj.insert("module", "ip_module");

    QString str = "cab " + QString::number(packet->rtuData.addr);
    obj.insert("cabinet", str);

    json.insert("uut_info", QJsonValue(obj));
}

void IP_BuildJson::ateInfo(IpDevPacket *packet, QJsonObject &json)
{
    QJsonObject obj;
    QString ip = (char *)packet->rtuData.data.ip;
    if(ip.isEmpty()) ip = "---";

    obj.insert("pdu_ip",  ip);
    obj.insert("pdu_num", packet->rtuData.addr); //

    obj.insert("pdu_type", "IP-PDU");
    obj.insert("pdu_spec", 1);
    obj.insert("pdu_line", packet->rtuData.data.lineNum);

    QString name = "IP-PDU " + QString::number(packet->rtuData.addr);
    obj.insert("pdu_name", name);

    json.insert("ate_info", QJsonValue(obj));
}

void IP_BuildJson::objData(IP_RtuRecvLine *ObjData, int id, QJsonObject &obj)
{
    int value = ObjData->vol.value[id] ;
    if(value >= 0) obj.insert("vol", value / COM_RATE_VOL);

    value = ObjData->cur.value[id] ;
    if(value >= 0) obj.insert("cur", value / COM_RATE_CUR);

    value = ObjData->pow[id];
    if(value >= 0) obj.insert("pow", value / COM_RATE_POW);

    value = ObjData->ele[id];
    if(value >= 0) obj.insert("ele", value / COM_RATE_ELE);

    value = ObjData->pf[id];
    if(value >= 0) obj.insert("PF", value / COM_RATE_PF);

    value = ObjData->sw[id];
    if(value >= 0) obj.insert("switch", value);
}

void IP_BuildJson::lineData(IP_RtuRecvLine *ObjData, QJsonObject &json)
{
    QJsonArray jsonArray;
    QString modeStr = "line";

    int num = ObjData->lineNum;
    for(int i=0; i<num; ++i)
    {
        QJsonObject subObj;
        subObj.insert("id", i);
        subObj.insert("name", modeStr +" "+ QString::number(i+1));

        objData(ObjData, i, subObj);
        jsonArray.append(subObj);
    }

    if(num > 0) json.insert(QString("%1_item_list").arg(modeStr), QJsonValue(jsonArray));
}

void IP_BuildJson::alarmItem(int index, int id, IP_sDataUnit &unit, double rate, QJsonArray &jsonArray)
{
    QString item, symbol, str="L";
    switch (index) {
    case 1:
        item = "相电压告警";
        symbol = "V";
        break;
    case 2:
        item = "相电流告警";
        symbol = "A";
        break;
    case 3:
        item = "输出位电流告警";
        symbol = "A";
        str = "Output";
        break;
    case 4:
        item = "输出位电压告警";
        symbol = "V";
        str = "Output";
        break;
    case 5:
        item = "温度告警";
        symbol = "°C";
        str = "温度";
        break;
    case 6:
        item = "湿度压告警";
        symbol = "%";
        str = "湿度";
        break;
    default:
        break;
    }

    QJsonObject subObj;
    QString contents = str + QString::number(id+1) + ", " +
            "当前值:" + unit.value[id]/rate + symbol + ", " +
            "最小值:" + unit.min[id]/rate + symbol + ", " +
            "最大值:" + unit.max[id]/rate + symbol + "; ";
    subObj.insert("item", item);
    subObj.insert("contents", contents);

    jsonArray.append(subObj);
}

void IP_BuildJson::thresholdItem(int index, int id, IP_sDataUnit &unit, double rate, QJsonObject &json)
{
    json.insert("id",  id);
    json.insert("type_index", index); //

    json.insert("min", unit.min[id] / rate);
    json.insert("max", unit.max[id] / rate);
    json.insert("cr_min", unit.min[id] / rate);
    json.insert("cr_max", unit.max[id] / rate);

    if(unit.alarm[id] == 2) {
        unit.alarm[id] = 3;
        alarmItem(index, id, unit, rate, mAlarmJsonArray);
    }
}

void IP_BuildJson::lineVolThreshold(IP_RtuRecvLine *ObjData, QJsonArray &jsonArray)
{
    int index = 1;

    int num = ObjData->lineNum;
    for(int i=0; i<num; ++i)
    {
        QJsonObject subObj;
        thresholdItem(index, i, ObjData->vol, COM_RATE_VOL, subObj);
        jsonArray.append(subObj);
    }
}

void IP_BuildJson::lineCurThreshold(IP_RtuRecvLine *ObjData, QJsonArray &jsonArray)
{
    int index = 2;

    int num = ObjData->lineNum;
    for(int i=0; i<num; ++i)
    {
        QJsonObject subObj;
        thresholdItem(index, i, ObjData->cur, COM_RATE_CUR, subObj);
        jsonArray.append(subObj);
    }
}

void IP_BuildJson::envThreshold(IP_RtuRecvLine *ObjData, QJsonArray &jsonArray)
{
    int index = 5;

    for(int i=0; i<1; ++i) {
        QJsonObject subObj;
        thresholdItem(index, i, ObjData->tem, COM_RATE_TEM, subObj);
        jsonArray.append(subObj);
    }

    index = 6;
    for(int i=0; i<1; ++i) {

        QJsonObject subObj;
        thresholdItem(index, i, ObjData->hum, COM_RATE_TEM, subObj);
        jsonArray.append(subObj);
    }
}

void IP_BuildJson::thresholds(IP_RtuRecvLine *ObjData, QJsonObject &json)
{
    QJsonArray jsonArray;

    lineVolThreshold(ObjData, jsonArray);
    lineCurThreshold(ObjData, jsonArray);
    envThreshold(ObjData, jsonArray);

    json.insert("threshold_item_list", QJsonValue(jsonArray));
}

void IP_BuildJson::envItem(int index, int id, const QString &name, int status, QJsonObject &json)
{
    json.insert("id",  id);
    json.insert("type_index", index); //

    json.insert("sensor", name);
    json.insert("status", status);
}

void IP_BuildJson::envSensor(IP_RtuRecvLine *ObjData, QJsonArray &jsonArray)
{
    int index = 1;

    for(int i=0; i<1; ++i) {
        QJsonObject subObj;
        envItem(index, i, "温度", ObjData->tem.value[i], subObj);
        jsonArray.append(subObj);
    }

    index = 2;
    for(int i=0; i<1; ++i) {
        QJsonObject subObj;
        envItem(index, i, "湿度", ObjData->hum.value[i], subObj);
        jsonArray.append(subObj);
    }
}

void IP_BuildJson::envs(IP_RtuRecvLine *ObjData, QJsonObject &json)
{
    QJsonArray jsonArray;
    envSensor(ObjData, jsonArray);

    json.insert("env_item_list", QJsonValue(jsonArray));
}

void IP_BuildJson::alarms(QJsonObject &json)
{
    if(!mAlarmJsonArray.isEmpty())
    {
        json.insert("alarm_item_list", QJsonValue(mAlarmJsonArray));
    }

    for(int i=0; i<mAlarmJsonArray.size(); ++i) {
        mAlarmJsonArray.removeFirst();
    }
}

void IP_BuildJson::devData(IpDevPacket *packet, QJsonObject &obj)
{
    IP_RtuRecvLine *devData = &(packet->rtuData.data);
    lineData(devData, obj);
    thresholds(devData, obj);
    envs(devData, obj);
    alarms(obj);

    for(int i=0; i<6; ++i)
        obj.insert("segment"+QString::number(i+1), "");
}





