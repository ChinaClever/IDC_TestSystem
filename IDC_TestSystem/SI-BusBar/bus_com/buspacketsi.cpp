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
        for(int j=1; j<=BUS_BOX_NUM; ++j) {

            sBoxData *box = &(mBus[i].box[j]);

            box->id = j;
            sprintf(box->name, "iBox-%d", j);

            for(int k=0; k<BUS_LOOP_NUM; ++k) {
                sprintf(box->loop[k].name, "loop-%d", k+1);
            }
        }
    }
}

void BusPacketSi::initBus()
{
     mBus[0].boxNum = 10;
    for(int i=0; i<BUS_NUM; ++i) {       
        sBoxData *box = &(mBus[i].box[0]);

        box->id = 0;
        sprintf(box->name, "0%d BUS", i+1);
    }
}

void BusPacketSi::initData()
{    
    initBus();
    initBox();
}
