#ifndef Z_RTURECV_H
#define Z_RTURECV_H
#include "z_rtusent.h"

#define Z_UNIT_NUM 43

struct Z_sDataUnit {
    ushort value[Z_UNIT_NUM]; // 值
    ushort min[Z_UNIT_NUM]; // 最小值
    ushort max[Z_UNIT_NUM]; // 最大值
    ushort alarm[Z_UNIT_NUM]; // 报警值 0表示未报警  1表示已报警 2表示已纪录

    ushort crMin[Z_UNIT_NUM]; // 最小值
    ushort crMax[Z_UNIT_NUM]; // 最大值
    ushort crAlarm[Z_UNIT_NUM]; // 报警值 0表示未报警  1表示已报警 2表示已纪录
};

/**
 * 数据对象：包括电流，电压，功率，电能，开关状态，插接位名称
 */
struct Z_sObjData
{
    ushort id, num;
    char name[NAME_SIZE];

    Z_sDataUnit vol; // 电压
    Z_sDataUnit cur; // 电流

    ushort pow[Z_UNIT_NUM]; // 功率
    ushort ele[Z_UNIT_NUM]; // 电能

    ushort pf[Z_UNIT_NUM]; // 功率因素
    ushort sw[Z_UNIT_NUM]; // 开关状态 0 表示未启用

    ushort activePow[Z_UNIT_NUM]; // 有功功率值
    ushort delay[Z_UNIT_NUM];
};

struct Z_sEnv
{
    Z_sDataUnit tem; // 温度
    Z_sDataUnit hum; // 湿度

    ushort door[3]; // 门禁
    ushort water[3]; // 水浸
    ushort smoke[3]; // 烟雾
};

struct Z_sRtuPacket {
    Z_sObjData line; // 相数据
    Z_sObjData loop; // 回响数据
    Z_sObjData output; //位数据
    Z_sEnv env;

    ushort hz[3]; // 频率
    ushort br;  // 00	表示波特率9600(00默认9600，01为4800，02为9600，03为19200，04为38400)

    ushort id, devSpec;
    ushort version;
    char ip[24], mac[40];
    ushort reserve;
};


struct Z_sRtuRecv {
    uchar addr; // 表示从机地址码
    uchar fn; // 表示功能码
    ushort len; // 表示数据字节数
    char offLine;
    Z_sRtuPacket data;
    ushort crc; // 检验码
};

class Z_RtuRecv
{
public:
    Z_RtuRecv();
    bool recvPacket(uchar *buf, int len, ushort reg, Z_sRtuRecv *pkt);

protected:
    void devTypeData(uchar *buf, int len, Z_sRtuPacket &pkt);
    void devIpAddr(uchar *buf, int len, Z_sRtuPacket &pkt);
    void devMac(uchar *buf, int len, Z_sRtuPacket &pkt);

private:
    bool rtuRecvPacket(uchar *buf, int len, ushort reg, Z_sRtuPacket &pkt);
    bool rtuRecvCrc(uchar *buf, int len, Z_sRtuRecv *msg);
    int rtuRecvHead(uchar *ptr,  Z_sRtuRecv *pkt);

    uchar *rtuRecvData(uchar *ptr, int num, uint *value);
    uchar *rtuRecvData(uchar *ptr, int num, ushort *value);
    uchar *rtuRecvData(uchar *ptr, int num, uchar *value);
};

#endif // Z_RTURECV_H
