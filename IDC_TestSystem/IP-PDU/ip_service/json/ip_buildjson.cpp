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

void IP_BuildJson::uutInfo(sDataPacket *packet, QJsonObject &json)
{
    QJsonObject obj;
    obj.insert("url", "www.clever.com");
    obj.insert("idc", "idc_test"); //

    obj.insert("room", "room_test");
    obj.insert("module", "ip_module");

    QString str = "cab " + QString::number(packet->id);
    obj.insert("cabinet", str);

    json.insert("uut_info", QJsonValue(obj));
}

void IP_BuildJson::ateInfo(sDataPacket *packet, QJsonObject &json)
{
    QJsonObject obj;
    QString ip = (char *)packet->ip;
    if(ip.isEmpty()) ip = "---";

    obj.insert("pdu_ip",  ip);
    obj.insert("pdu_num", packet->id); //

    obj.insert("pdu_type", "IP-PDU");
    obj.insert("pdu_spec", 1);
    obj.insert("pdu_line", packet->data.lineNum);

    QString name = "IP-PDU " + QString::number(packet->id);
    obj.insert("pdu_name", name);

    json.insert("ate_info", QJsonValue(obj));
}





