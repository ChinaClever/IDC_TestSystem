#ifndef BUSPACKETSI_H
#define BUSPACKETSI_H
#include <QtCore>

#define BUS_LOOP_NUM 9
#define BUS_LINE_NUM 3 // 三相
#define BUS_BOX_NUM 20 // 插接箱数量
#define BUS_NUM 4  // 四条母线
#define BUS_NAME_LEN	32 // 名称最大长度
#define BUS_SENSOR_NUM 3 // 二个传感器
#define BUS_ARRAY_LEN 255 //一包数据最长

/**
 * 数据单元：包括当前值，阈值，临界值，告警状态等
 */
struct BUS_sDataUnit
{
    int value; // 值
    int min; // 最小值
    int max; // 最大值
    int alarm; // 告警值 0表示未告警  1表示已告警 2表示已记录

    int crMin; // 临界最小值
    int crMax; // 临界最大值
    int crAlarm; // 临界告警值
};

/**
 * 插接位数据对象：包括电流，电压，功率，电能，开关状态，插接位名称
 */
struct BUS_sObjUnit
{
    int id;
    char name[BUS_NAME_LEN];

    BUS_sDataUnit vol; // 电压
    BUS_sDataUnit cur;  // 电流

    int pow; // 功率
    int apPow; // 袖在功率
    int ele; // 电能
    int pf; // 功率因素
    int sw; // 开关状态

    int ratedCur; // 额定电流
    int wave; // 谐波值
    int tem;
};


/**
 * 环境数据结构体
 */
struct BUS_sEnvData {
    BUS_sDataUnit tem; // 温度
    BUS_sDataUnit hum; // 湿度
};

struct BUS_RtuCount
{
    int count;
    int okCount;
    int errCount;
};


/**
 * 插接箱数据结构体：包括最多三个插接位，插接箱名称
 */
struct sBoxData {
    char id;
    char name[BUS_NAME_LEN];

    char offLine; // 离线标识
    int loopNum; // 回路数量
    char version;

    BUS_RtuCount count;
    BUS_sObjUnit tg; // 回路数据
    BUS_sObjUnit line[BUS_LINE_NUM]; // 回路数据
    BUS_sObjUnit loop[BUS_LOOP_NUM]; // 回路数据
    BUS_sEnvData env[BUS_SENSOR_NUM]; // 环境状态

    char boxAlarm, boxVolAlarm, boxCurAlarm, boxEnvAlarm; // 插接箱告警
    char boxStatus; // 插接箱状态
    char boxSpec; //  0 表示 SI  1 表示 IP

    int ratedCur; // 额定电流
    int rate; // 电压频率
    char dc; // 交直流标志位
};

/**
 * 母线数据结构体：包括插接箱数据，电压频率 母线名称
 */
struct sBusData{
    int boxNum; // 插接箱数量
    sBoxData   box[BUS_BOX_NUM+1];  // 最多20个插接箱
};


class BusPacketSi
{
    BusPacketSi();
public:
    static BusPacketSi *bulid();

    sBusData *getBus(int bus) {return &(mBus[bus]);}
    sBoxData *getBox(int bus, int box) {return &(mBus[bus].box[box]);}

private:
    sBusData mBus[BUS_NUM];
};

#endif // BUSPACKETSI_H
