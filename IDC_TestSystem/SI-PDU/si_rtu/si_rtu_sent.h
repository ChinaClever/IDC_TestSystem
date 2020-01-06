#ifndef SI_RTU_SENT_H
#define SI_RTU_SENT_H

#include "rtucom/rtuthread.h"
#include "serialportwid.h"
#include "si_rtu_setcmd.h"

//#define SI_RTU_ONE_LEN 0x1A  // 单相数据长度
//#define SI_RTU_THREE_LEN 0x4A  // 三相数据长度
#define SI_RTU_ONE_LEN 0x21  // 单相数据长度
#define SI_RTU_THREE_LEN 0x51  // 三相数据长度

struct SI_Rtu_Sent : public sRtuSentCom{
    SI_Rtu_Sent(){len=SI_RTU_ONE_LEN;}
};

class SI_RtuSent
{
public:
    int sentDataBuff(uchar addr, uchar line, uchar *buf);
    int sentCmdBuff(uchar addr, ushort reg, ushort value, uchar *buf);
};

ushort si_rtu_crc(uchar *buf, int len);

#endif // SI_RTU_SENT_H
