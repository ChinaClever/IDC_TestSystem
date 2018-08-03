#ifndef M_RTURECV_H
#define M_RTURECV_H
#include "m_rtusent.h"

#define M_UNIT_NUM 43

struct M_sDataUnit {
    ushort value[M_UNIT_NUM]; // 值
    ushort min[M_UNIT_NUM]; // 最小值
    ushort max[M_UNIT_NUM]; // 最大值
    ushort alarm[M_UNIT_NUM]; // 报警值 0表示未报警  1表示已报警 2表示已纪录

    ushort crMin[M_UNIT_NUM]; // 最小值
    ushort crMax[M_UNIT_NUM]; // 最大值
    ushort crAlarm[M_UNIT_NUM]; // 报警值 0表示未报警  1表示已报警 2表示已纪录
};

/**
 * 数据对象：包括电流，电压，功率，电能，开关状态，插接位名称
 */
struct M_sObjData
{
    int id, num;
    char name[NAME_SIZE];

    sDataUnit vol; // 电压
    sDataUnit cur; // 电流

    ushort pow[M_UNIT_NUM]; // 功率
    uint ele[M_UNIT_NUM]; // 电能

    uchar pf[M_UNIT_NUM]; // 功率因素
    uchar sw[M_UNIT_NUM]; // 开关状态 0 表示未启用

    ushort activePow[M_UNIT_NUM]; // 有功功率值
};


struct M_sRtuPacket {
    M_sObjData line; // 相数据
    M_sObjData output; //位数据
    ushort hz[3]; // 频率

    M_sDataUnit tem; // 温度
    M_sDataUnit hum; // 湿度
    ushort br;  // 00	表示波特率9600(00默认9600，01为4800，02为9600，03为19200，04为38400)

    ushort version;
    uchar ip[18];
    ushort reserve;
};


struct M_sRtuRecv {
    uchar addr; // 表示从机地址码
    uchar fn; // 表示功能码
    ushort len; // 表示数据字节数
    char offLine;
    M_sRtuPacket data;
    ushort crc; // 检验码
};



class M_RtuRecv
{
public:
    M_RtuRecv();
    bool recvPacket(uchar *buf, int len, M_sRtuRecv *pkt);

protected:
    bool rtuRecvPacket(uchar *buf, int len, M_sRtuRecv *pkt);
    bool rtuRecvCrc(uchar *buf, int len, M_sRtuRecv *msg);
    int rtuRecvHead(uchar *ptr,  M_sRtuRecv *pkt);

};

#endif // M_RTURECV_H
