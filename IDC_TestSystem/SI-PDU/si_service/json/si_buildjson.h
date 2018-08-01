#ifndef SI_BUILDJSON_H
#define SI_BUILDJSON_H
#include "websocket/websocketclient.h"
#include "si_com/sidatapackets.h"

class SI_BuildJson : public BuildJson
{
    SI_BuildJson();
public:
    static SI_BuildJson *bulid();

protected:
    void uutInfo(sDataPacket *packet, QJsonObject &json);
    void ateInfo(sDataPacket *packet, QJsonObject &json);

};

#endif // SI_BUILDJSON_H
