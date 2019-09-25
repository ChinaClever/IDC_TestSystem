#ifndef BUSPACKETSI_H
#define BUSPACKETSI_H
#include "datapacket.h"

#define BUS_NUM 4  // 四条母线

/**
 * 母线数据结构体：包括插接箱数据，电压频率 母线名称
 */
typedef sDevPackets sBusData;


class BusPacketSi
{
    BusPacketSi();
public:
    static BusPacketSi *bulid();

    sBusData *getBus(int bus) {return &(mBus[bus]);}
    char *getBusName(int bus) {return mBus[bus].dev[0].name;}
    sDataPacket *getBox(int bus, int box) {return &(mBus[bus].dev[box]);}

protected:
    void initData();
    void initBox();
    void initBus();
private:
    sBusData mBus[BUS_NUM];
};

#endif // BUSPACKETSI_H
