#ifndef SI_BUILDJSON_H
#define SI_BUILDJSON_H
#include "websocket/websocketclient.h"
#include "si_com/sidatapackets.h"

class SI_BuildJson
{
    SI_BuildJson();
public:
    static SI_BuildJson *bulid();

    bool getJson(SiDevPacket *packet, QJsonObject &json);
    bool saveJson(const QString &name, QJsonObject &json);

protected:
    void head(SiDevPacket *packet,QJsonObject &obj);
    void uutInfo(SiDevPacket *packet, QJsonObject &json);
    void ateInfo(SiDevPacket *packet, QJsonObject &json);

    void objData(SI_RtuRecvLine *ObjData, int id, QJsonObject &obj);
    void lineData(SI_RtuRecvLine *ObjData, QJsonObject &json);

    void thresholdItem(int index, int id, SI_sDataUnit &unit, double rate, QJsonObject &json);
    void lineVolThreshold(SI_RtuRecvLine *ObjData, QJsonArray &jsonArray);
    void lineCurThreshold(SI_RtuRecvLine *ObjData, QJsonArray &jsonArray);
    void envThreshold(SI_RtuRecvLine *ObjData, QJsonArray &jsonArray);
    void thresholds(SI_RtuRecvLine *ObjData, QJsonObject &json);

    void envItem(int index, int id, const QString &name, int status, QJsonObject &json);
    void envSensor(SI_RtuRecvLine *ObjData, QJsonArray &jsonArray);
    void envs(SI_RtuRecvLine *ObjData, QJsonObject &json);

    void alarmItem(int index, int id, SI_sDataUnit &unit, double rate, QJsonArray &jsonArray);
    void alarms(QJsonObject &json);

    void devData(SiDevPacket *packet, QJsonObject &obj);

private:
    QJsonArray mAlarmJsonArray;
};

#endif // SI_BUILDJSON_H
