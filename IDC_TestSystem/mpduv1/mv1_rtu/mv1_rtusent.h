#ifndef MV1_RTUSENT_H
#define MV1_RTUSENT_H
#include "serialportwid.h"
#include "mv1_rturegenum.h"

struct MV1_Rtu_Sent : public sRtuSentCom{
    MV1_Rtu_Sent(){len=0;}
};


class MV1_RtuSent
{
public:
    MV1_RtuSent();
    int sentDataBuff(uchar addr,  ushort reg, ushort len, uchar *buf);
    int sentCmdBuff(uchar addr, ushort reg, ushort value, uchar *buf);

protected:
    QMutex *mMutex;
    MV1_Rtu_Sent *mMsg;
};

#endif // MV1_RTUSENT_H
