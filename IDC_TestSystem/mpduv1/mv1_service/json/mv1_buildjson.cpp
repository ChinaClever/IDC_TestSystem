﻿/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1_buildjson.h"

MV1_BuildJson::MV1_BuildJson()
{

}

MV1_BuildJson *MV1_BuildJson::bulid()
{
    static MV1_BuildJson* sington = nullptr;
    if(sington == nullptr)
        sington = new MV1_BuildJson();
    return sington;
}

void MV1_BuildJson::uutInfo(sDataPacket *packet, QJsonObject &json)
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

void MV1_BuildJson::ateInfo(sDataPacket *packet, QJsonObject &json)
{
    QJsonObject obj;
    QString ip = (char *)packet->ip;
    if(ip.isEmpty()) ip = "---";

    obj.insert("pdu_ip",  ip);
    obj.insert("pdu_num", packet->id); //

    obj.insert("pdu_type", "MPDUV1");
    obj.insert("pdu_spec", packet->devSpec);
    obj.insert("pdu_line", packet->data.lineNum);

    QString name = "MPDUMV1 " + QString::number(packet->id);
    obj.insert("pdu_name", name);

    json.insert("ate_info", QJsonValue(obj));
}

