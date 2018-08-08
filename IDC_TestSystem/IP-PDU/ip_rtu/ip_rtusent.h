#ifndef IP_RTUSENT_H
#define IP_RTUSENT_H
#include "serialportwid.h"

#define IP_RTU_ONE_LEN 49  // 单相数据长度
#define IP_RTU_THREE_LEN 58  // 三相数据长度

struct IP_Rtu_Sent : public Rtu_Sent_Com{
    IP_Rtu_Sent(){len=IP_RTU_ONE_LEN;}
};


class IP_RtuSent
{
public:
    IP_RtuSent();
    int sentDataBuff(uchar addr, uchar line, uchar *buf);
    int sentCmdBuff(uchar addr, ushort reg, ushort value, uchar *buf);
};

#endif // IP_RTUSENT_H
