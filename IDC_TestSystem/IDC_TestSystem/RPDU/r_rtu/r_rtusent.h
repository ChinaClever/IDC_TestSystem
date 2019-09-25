#ifndef R_RTUSENT_H
#define R_RTUSENT_H
#include "serialportwid.h"
#include "r_rturegenum.h"

struct R_Rtu_Sent : public sRtuSentCom{
    R_Rtu_Sent(){len=0;}
};

class R_RtuSent
{
public:
    R_RtuSent();
    int sentDataBuff(uchar addr,  ushort reg, ushort len, uchar *buf);
    int sentCmdBuff(uchar addr, ushort reg, ushort value, uchar *buf);

protected:
    QMutex *mMutex;
    R_Rtu_Sent *mMsg;
};

#endif // R_RTUSENT_H
