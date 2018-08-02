#ifndef IP_BUILDJSON_H
#define IP_BUILDJSON_H
#include "websocket/webservicethread.h"

class IP_BuildJson : public BuildJson
{
    IP_BuildJson();
public:
    static IP_BuildJson *bulid();

protected:
    void uutInfo(sDataPacket *packet, QJsonObject &json);
    void ateInfo(sDataPacket *packet, QJsonObject &json);
};

#endif // IP_BUILDJSON_H
