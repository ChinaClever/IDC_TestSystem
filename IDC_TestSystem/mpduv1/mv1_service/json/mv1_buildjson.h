#ifndef MV1_BUILDJSON_H
#define MV1_BUILDJSON_H
#include "websocket/webservicethread.h"

class MV1_BuildJson: public BuildJson
{
    MV1_BuildJson();
public:
    static MV1_BuildJson *bulid();

protected:
    void uutInfo(sDataPacket *packet, QJsonObject &json);
    void ateInfo(sDataPacket *packet, QJsonObject &json);
};

#endif // MV1_BUILDJSON_H
