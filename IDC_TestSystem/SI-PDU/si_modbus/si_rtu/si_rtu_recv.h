#ifndef SI_RTU_RECV_H
#define SI_RTU_RECV_H
#include "si_rtu_sent.h"

#define SI_LINE_NUM 3

struct SI_sDataUnit {
    ushort value[SI_LINE_NUM]; // 值
    ushort min[SI_LINE_NUM]; // 最小值
    ushort max[SI_LINE_NUM]; // 最大值
    ushort alarm[SI_LINE_NUM]; // 报警值 0表示未报警  1表示已报警 2表示已纪录
};


struct SI_RtuRecvLine {
    SI_sDataUnit vol; // 电压值
    SI_sDataUnit cur; // 电流值
    uint ele[SI_LINE_NUM]; // 电能值
    ushort pow[SI_LINE_NUM]; // 功率值

    SI_sDataUnit tem; // 温度
    SI_sDataUnit hum; // 湿度
    uchar br;  // 00	表示波特率9600(00默认9600，01为4800，02为9600，03为19200，04为38400)

    ushort activePow[SI_LINE_NUM]; // 有功功率值
    uchar pf[SI_LINE_NUM]; // 功率因素
    uchar sw[SI_LINE_NUM]; // 开关  01表示断路器闭合，00表示打开)
    uchar lineNum; // 表示单三相 (01表示单相，03表示三相)
};


struct SI_Rtu_Recv {
    uchar addr; // 表示从机地址码
    uchar fn; // 表示功能码
    ushort len; // 表示数据字节数

    SI_RtuRecvLine data;


    ushort crc; // 检验码
};

class SI_RtuRecv
{
public:
    SI_RtuRecv();
};

#endif // SI_RTU_RECV_H
