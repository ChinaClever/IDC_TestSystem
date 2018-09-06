#ifndef Z_RTUSENT_H
#define Z_RTUSENT_H
#include "serialportwid.h"
#include "z_rturegenum.h"

struct Z_Rtu_Sent : public sRtuSentCom{
    Z_Rtu_Sent(){len=0;}
};

class Z_RtuSent
{
public:
    Z_RtuSent();
    int sentDataBuff(uchar addr,  ushort reg, ushort len, uchar *buf);
    int sentCmdBuff(uchar addr, ushort reg, ushort value, uchar *buf);

protected:
    QMutex *mMutex;
    Z_Rtu_Sent *mMsg;
};

#endif // Z_RTUSENT_H
