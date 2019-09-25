#ifndef R_BUILDJSON_H
#define R_BUILDJSON_H
#include "websocket/webservicethread.h"

class R_BuildJson: public BuildJson
{
    R_BuildJson();
public:
    static R_BuildJson *bulid();

protected:
    void uutInfo(sDataPacket *packet, QJsonObject &json);
    void ateInfo(sDataPacket *packet, QJsonObject &json);
};

#endif // R_BUILDJSON_H
