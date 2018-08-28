#ifndef Z_BUILDJSON_H
#define Z_BUILDJSON_H
#include "websocket/webservicethread.h"

class Z_BuildJson: public BuildJson
{
    Z_BuildJson();
public:
    static Z_BuildJson *bulid();

protected:
    void uutInfo(sDataPacket *packet, QJsonObject &json);
    void ateInfo(sDataPacket *packet, QJsonObject &json);
};

#endif // Z_BUILDJSON_H
