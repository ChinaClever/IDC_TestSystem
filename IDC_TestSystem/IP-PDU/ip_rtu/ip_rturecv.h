#ifndef IP_RTURECV_H
#define IP_RTURECV_H
#include "ip_rtusent.h"

#define IP_LINE_NUM 3

struct IP_sDataUnit {
    ushort value[IP_LINE_NUM]; // 值
    ushort min[IP_LINE_NUM]; // 最小值
    ushort max[IP_LINE_NUM]; // 最大值
    ushort alarm[IP_LINE_NUM]; // 报警值 0表示未报警  1表示已报警 2表示已纪录
};


struct IP_RtuRecvLine {
    IP_sDataUnit vol; // 电压值
    IP_sDataUnit cur; // 电流值
    uint ele[IP_LINE_NUM]; // 电能值
    ushort pow[IP_LINE_NUM]; // 功率值
    ushort hz[IP_LINE_NUM]; // 频率

    IP_sDataUnit tem; // 温度
    IP_sDataUnit hum; // 湿度
    ushort br;  // 00	表示波特率9600(00默认9600，01为4800，02为9600，03为19200，04为38400)

    ushort activePow[IP_LINE_NUM]; // 有功功率值
    uchar pf[IP_LINE_NUM]; // 功率因数
    ushort sw[IP_LINE_NUM]; // 开关  01表示断路器闭合，00表示打开)
    ushort lineNum; // 表示单三相 (01表示单相，03表示三相)
    ushort version;
    uchar ip[18];
    ushort reserve;
};


struct IP_Rtu_Recv {
    uchar addr; // 表示从机地址码
    uchar fn; // 表示功能码
    ushort len; // 表示数据字节数
    char offLine;
    char v;
    IP_RtuRecvLine data;
    ushort crc; // 检验码
};


class IP_RtuRecv
{
public:
     bool recvPacket(uchar *buf, int len, IP_Rtu_Recv *pkt);
};

#endif // IP_RTURECV_H
