#ifndef M_BUILDJSON_H
#define M_BUILDJSON_H
#include "websocket/webservicethread.h"

class M_BuildJson: public BuildJson
{
    M_BuildJson();
public:
    static M_BuildJson *bulid();

protected:
    void uutInfo(sDataPacket *packet, QJsonObject &json);
    void ateInfo(sDataPacket *packet, QJsonObject &json);
};

#endif // M_BUILDJSON_H
