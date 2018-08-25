/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "z_buildjson.h"

Z_BuildJson::Z_BuildJson()
{

}

Z_BuildJson *Z_BuildJson::bulid()
{
    static Z_BuildJson* sington = nullptr;
    if(sington == nullptr)
        sington = new Z_BuildJson();
    return sington;
}

void Z_BuildJson::uutInfo(sDataPacket *packet, QJsonObject &json)
{
    QJsonObject obj;
    obj.insert("url", "www.clever.com");
    obj.insert("idc", "idc_test"); //

    obj.insert("room", "room_test");
    obj.insert("module", "z_module");

    QString str = "cab " + QString::number(packet->id);
    obj.insert("cabinet", str);

    json.insert("uut_info", QJsonValue(obj));
}

void Z_BuildJson::ateInfo(sDataPacket *packet, QJsonObject &json)
{
    QJsonObject obj;
    QString ip = (char *)packet->ip;
    if(ip.isEmpty()) ip = "---";

    obj.insert("pdu_ip",  ip);
    obj.insert("pdu_num", packet->id); //

    obj.insert("pdu_type", "Z-PDU");
    obj.insert("pdu_spec", packet->devSpec);
    obj.insert("pdu_line", packet->data.lineNum);

    QString name = "Z-PDU " + QString::number(packet->id);
    obj.insert("pdu_name", name);

    json.insert("ate_info", QJsonValue(obj));
}
