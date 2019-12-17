#ifndef MV1_RTURECV_H
#define MV1_RTURECV_H
#include "mv1_rtusent.h"
#include "common/rtucom/rtuzmrecv.h"

#define MV1_UNIT_NUM 43

struct MV1_sDataUnit {
    ushort value[MV1_UNIT_NUM]; // 值
    ushort min[MV1_UNIT_NUM]; // 最小值
    ushort max[MV1_UNIT_NUM]; // 最大值
    ushort alarm[MV1_UNIT_NUM]; // 报警值 0表示未报警  1表示已报警 2表示已纪录

    ushort crMin[MV1_UNIT_NUM]; // 最小值
    ushort crMax[MV1_UNIT_NUM]; // 最大值
    ushort crAlarm[MV1_UNIT_NUM]; // 报警值 0表示未报警  1表示已报警 2表示已纪录
};

/**
 * 数据对象：包括电流，电压，功率，电能，开关状态，插接位名称
 */
struct MV1_sObjData
{
    ushort id, num;
    char name[NAME_SIZE];

    MV1_sDataUnit vol; // 电压
    MV1_sDataUnit cur; // 电流

    ushort pow[MV1_UNIT_NUM]; // 功率
    uint ele[MV1_UNIT_NUM]; // 电能

    ushort pf[MV1_UNIT_NUM]; // 功率因数
    ushort sw[MV1_UNIT_NUM]; // 开关状态 0 表示未启用

    ushort activePow[MV1_UNIT_NUM]; // 有功功率值
    ushort delay[MV1_UNIT_NUM];
};


struct MV1_sRtuPacket {
    MV1_sObjData line; // 相数据
    MV1_sObjData output; //位数据
    ushort hz[3]; // 频率

    MV1_sDataUnit tem; // 温度
    MV1_sDataUnit hum; // 湿度
    ushort br;  // 00	表示波特率9600(00默认9600，01为4800，02为9600，03为19200，04为38400)

    ushort id, devSpec;
    ushort version;
    uchar ip[18];
    ushort reserve;
};


struct MV1_sRtuRecv {
    uchar addr; // 表示从机地址码
    uchar fn; // 表示功能码
    ushort len; // 表示数据字节数
    char offLine;
    MV1_sRtuPacket data;
    ushort crc; // 检验码
};


class MV1_RtuRecv
{
public:
    MV1_RtuRecv();
    bool recvPacket(uchar *buf, int len, ZM_sRtuRecv *pkt);

protected:
    bool rtuRecvPacket(uchar *buf, int len,ZM_sRtuRecv *pkt);
    bool rtuRecvCrc(uchar *buf, int len, ZM_sRtuRecv *msg);
    int rtuRecvHead(uchar *ptr,  ZM_sRtuRecv *pkt);

    uchar *rtuRecvData(uchar *ptr, int num, uint *value);
    uchar *rtuRecvData(uchar *ptr, int num, ushort *value);
    uchar *rtuRecvData(uchar *ptr, int num, ushort *value1,uint *value2);
    uchar *rtuRecvData(uchar *ptr, int num, uint *value1,ushort *value2);

    void rtuLineData(uchar *buf, ZM_sObjData &pkt);
    void rtuOutputData(uchar *buf, ZM_sObjData &pkt);
    void rtuOutputEle(uchar *buf, ZM_sObjData &pkt);

    void rtuEnvData(uchar *buf, ZM_sRtuPacket &pkt);
    void rtuLineThreshold(uchar *buf, ZM_sObjData &pkt);
    void rtuOutputThreshold(uchar *buf, ZM_sObjData &pkt);

    void rtuLineSw(uchar *buf, ZM_sObjData &pkt);
    void rtuOutputSw(uchar *buf, ZM_sObjData &pkt);
    void rtuEnvThreshold(uchar *buf, ZM_sRtuPacket &pkt);
    void rtuDevAddr(uchar *buf, ZM_sRtuPacket &pkt);
    void rtuLineNum(uchar *buf, ZM_sObjData &pkt);
};

#endif // MV1_RTURECV_H
