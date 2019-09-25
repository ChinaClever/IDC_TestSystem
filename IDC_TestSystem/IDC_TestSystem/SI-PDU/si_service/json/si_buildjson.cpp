/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "si_buildjson.h"

SI_BuildJson::SI_BuildJson()
{

}

SI_BuildJson *SI_BuildJson::bulid()
{
    static SI_BuildJson* sington = nullptr;
    if(sington == nullptr)
        sington = new SI_BuildJson();
    return sington;
}


void SI_BuildJson::uutInfo(sDataPacket *packet, QJsonObject &json)
{
    QJsonObject obj;
    obj.insert("url", "www.clever.com");
    obj.insert("idc", "idc_test"); //

    obj.insert("room", "room_test");
    obj.insert("module", "si_module");

    QString str = "cab " + QString::number(packet->id);
    obj.insert("cabinet", str);

    json.insert("uut_info", QJsonValue(obj));
}

void SI_BuildJson::ateInfo(sDataPacket *packet, QJsonObject &json)
{
    QJsonObject obj;
    obj.insert("pdu_ip",  "---");
    obj.insert("pdu_num", packet->id); //

    obj.insert("pdu_type", "Si-PDU");
    obj.insert("pdu_spec", 1);
    obj.insert("pdu_line", packet->data.lineNum);

    QString name = "SI-PDU " + QString::number(packet->id);
    obj.insert("pdu_name", name);

    json.insert("ate_info", QJsonValue(obj));
}




