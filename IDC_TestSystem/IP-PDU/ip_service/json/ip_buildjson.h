#ifndef IP_BUILDJSON_H
#define IP_BUILDJSON_H
#include "websocket/websocketclient.h"
#include "ip_com/ipdatapackets.h"

class IP_BuildJson
{
    IP_BuildJson();
public:
    static IP_BuildJson *bulid();

    bool getJson(IpDevPacket *packet, QJsonObject &json);
    bool saveJson(const QString &name, QJsonObject &json);

protected:
    void head(IpDevPacket *packet,QJsonObject &obj);
    void uutInfo(IpDevPacket *packet, QJsonObject &json);
    void ateInfo(IpDevPacket *packet, QJsonObject &json);

    void objData(IP_RtuRecvLine *ObjData, int id, QJsonObject &obj);
    void lineData(IP_RtuRecvLine *ObjData, QJsonObject &json);

    void thresholdItem(int index, int id, IP_sDataUnit &unit, double rate, QJsonObject &json);
    void lineVolThreshold(IP_RtuRecvLine *ObjData, QJsonArray &jsonArray);
    void lineCurThreshold(IP_RtuRecvLine *ObjData, QJsonArray &jsonArray);
    void envThreshold(IP_RtuRecvLine *ObjData, QJsonArray &jsonArray);
    void thresholds(IP_RtuRecvLine *ObjData, QJsonObject &json);

    void envItem(int index, int id, const QString &name, int status, QJsonObject &json);
    void envSensor(IP_RtuRecvLine *ObjData, QJsonArray &jsonArray);
    void envs(IP_RtuRecvLine *ObjData, QJsonObject &json);

    void alarmItem(int index, int id, IP_sDataUnit &unit, double rate, QJsonArray &jsonArray);
    void alarms(QJsonObject &json);

    void devData(IpDevPacket *packet, QJsonObject &obj);

private:
    QJsonArray mAlarmJsonArray;
};

#endif // IP_BUILDJSON_H
