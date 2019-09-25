/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "buspacketsi.h"

BusPacketSi::BusPacketSi()
{
    memset(&mBus, 0, sizeof(sBusData)*BUS_NUM);
    initData();
}

BusPacketSi *BusPacketSi::bulid()
{
    static BusPacketSi* sington = nullptr;
    if(sington == nullptr)
        sington = new BusPacketSi();
    return sington;
}

void BusPacketSi::initBox()
{
    for(int i=0; i<BUS_NUM; ++i) {
        for(int j=1; j<=DEV_NUM; ++j) {

            sDataPacket *box = &(mBus[i].dev[j]);

            box->id = j;
            sprintf(box->name, "iBox-%d", j);

            for(int k=0; k<LOOP_NUM; ++k) {
                sprintf(box->data.loop[k].name, "loop-%d", k+1);
            }
        }
    }
}

void BusPacketSi::initBus()
{
     mBus[0].devNum = 10;
    for(int i=0; i<BUS_NUM; ++i) {       
        sDataPacket *box = &(mBus[i].dev[0]);

        box->id = 0;
        sprintf(box->name, "0%d BUS", i+1);
    }
}

void BusPacketSi::initData()
{    
    initBus();
    initBox();
}
