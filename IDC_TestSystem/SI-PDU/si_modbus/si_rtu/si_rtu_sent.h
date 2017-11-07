#ifndef SI_RTU_SENT_H
#define SI_RTU_SENT_H

#include "serialportwid.h"
#include "si_rtu_setcmd.h"

#define SI_RTU_ONE_LEN 0x1A  // 单相数据长度
#define SI_RTU_THREE_LEN 0x4A  // 三相数据长度

struct SI_Rtu_Sent {
    SI_Rtu_Sent():fn(3),reg(0),len(SI_RTU_ONE_LEN){}
    uchar addr; // 表示从机地址码
    uchar fn;  // 表示功能码
    ushort reg; // 表示寄存器首地址
    ushort len; // 表示数据长度
    ushort crc; // 表示CRC校验
};

class SI_RtuSent
{
public:
    SI_RtuSent();


    ///////////============
    ///
    ///
    /// 增加命令发送命令
    ///
    ///
};

ushort si_rtu_crc(uchar *buf, int len);

#endif // SI_RTU_SENT_H
