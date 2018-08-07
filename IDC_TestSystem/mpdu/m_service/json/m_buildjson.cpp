/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "m_buildjson.h"

M_BuildJson::M_BuildJson()
{

}

M_BuildJson *M_BuildJson::bulid()
{
    static M_BuildJson* sington = nullptr;
    if(sington == nullptr)
        sington = new M_BuildJson();
    return sington;
}

void M_BuildJson::uutInfo(sDataPacket *packet, QJsonObject &json)
{
    QJsonObject obj;
    obj.insert("url", "www.clever.com");
    obj.insert("idc", "idc_test"); //

    obj.insert("room", "room_test");
    obj.insert("module", "m_module");

    QString str = "cab " + QString::number(packet->id);
    obj.insert("cabinet", str);

    json.insert("uut_info", QJsonValue(obj));
}

void M_BuildJson::ateInfo(sDataPacket *packet, QJsonObject &json)
{
    QJsonObject obj;
    QString ip = (char *)packet->ip;
    if(ip.isEmpty()) ip = "---";

    obj.insert("pdu_ip",  ip);
    obj.insert("pdu_num", packet->id); //

    obj.insert("pdu_type", "M-PDU");
    obj.insert("pdu_spec", packet->devSpec);
    obj.insert("pdu_line", packet->data.lineNum);

    QString name = "M-PDU " + QString::number(packet->id);
    obj.insert("pdu_name", name);

    json.insert("ate_info", QJsonValue(obj));
}

