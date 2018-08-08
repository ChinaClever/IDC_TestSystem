#ifndef M_RTUSENT_H
#define M_RTUSENT_H
#include "serialportwid.h"
#include "m_rturegenum.h"

struct M_Rtu_Sent : public Rtu_Sent_Com{
    M_Rtu_Sent(){len=0;}
};


class M_RtuSent
{
public:
    M_RtuSent();
    int sentDataBuff(uchar addr,  ushort reg, ushort len, uchar *buf);
    int sentCmdBuff(uchar addr, ushort reg, ushort value, uchar *buf);

protected:
    QMutex *mMutex;
    M_Rtu_Sent *mMsg;
};

#endif // M_RTUSENT_H
