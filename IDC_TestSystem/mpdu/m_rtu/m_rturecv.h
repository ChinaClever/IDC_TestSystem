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
    ushort id, num;
    char name[NAME_SIZE];

    M_sDataUnit vol; // 电压
    M_sDataUnit cur; // 电流

    ushort pow[M_UNIT_NUM]; // 功率
    uint ele[M_UNIT_NUM]; // 电能

    ushort pf[M_UNIT_NUM]; // 功率因素
    ushort sw[M_UNIT_NUM]; // 开关状态 0 表示未启用

    ushort activePow[M_UNIT_NUM]; // 有功功率值
    ushort delay[M_UNIT_NUM];
};


struct M_sRtuPacket {
    M_sObjData line; // 相数据
    M_sObjData output; //位数据
    ushort hz[3]; // 频率

    M_sDataUnit tem; // 温度
    M_sDataUnit hum; // 湿度
    ushort br;  // 00	表示波特率9600(00默认9600，01为4800，02为9600，03为19200，04为38400)

    ushort id, devSpec;
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

    uchar *rtuRecvData(uchar *ptr, int num, uint *value);
    uchar *rtuRecvData(uchar *ptr, int num, ushort *value);

    void rtuLineData(uchar *buf, M_sObjData &pkt);
    void rtuOutputData(uchar *buf, M_sObjData &pkt);
    void rtuOutputEle(uchar *buf, M_sObjData &pkt);

    void rtuEnvData(uchar *buf, M_sRtuPacket &pkt);
    void rtuLineThreshold(uchar *buf, M_sObjData &pkt);
    void rtuOutputThreshold(uchar *buf, M_sObjData &pkt);

    void rtuLineSw(uchar *buf, M_sObjData &pkt);
    void rtuOutputSw(uchar *buf, M_sRtuPacket &pkt);
    void rtuEnvThreshold(uchar *buf, M_sRtuPacket &pkt);
    void rtuDevAddr(uchar *buf, M_sRtuPacket &pkt);
    void rtuLineNum(uchar *buf, M_sObjData &pkt);
};

#endif // M_RTURECV_H
