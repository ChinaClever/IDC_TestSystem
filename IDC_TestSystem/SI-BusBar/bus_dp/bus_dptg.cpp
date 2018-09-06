/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "bus_dptg.h"

BUS_DpTg::BUS_DpTg()
{

}


/**
 * @brief 获取平均数据 0视无效数据
 * @param data
 */
int BUS_DpTg::averData(int *data, int len)
{
    int size=0, value=0,temp;

    for(int i=0; i< len; ++i)
    {
        temp = data[i];
        if(temp > 0) {
            size++;
            value += temp;
        } else
            temp = 0;
    }

    if(size > 0)
        value /= size;

    return value;
}

void BUS_DpTg::bulidPf(sObjData *unit)
{
    unit->activePow = unit->vol.value * unit->cur.value;

    if(unit->pow > unit->activePow) {
        unit->pow = unit->activePow;
    }

    if(unit->activePow > 0) {
        unit->pf = (unit->pow * 100.0 / unit->activePow);
        if(unit->pf > 99) unit->pf = 99;
    } else {
        unit->pf = 0;
    }

    //  tg->pf = averData(obj->pf);
}

void BUS_DpTg::tgObj(sDevData *box)
{
    sObjData *tg = &(box->tg);
    memset(tg, 0, sizeof(sObjData));
    for(int i=0; i<box->loopNum; ++i)
    {
        sObjData *obj = &(box->loop[i]);
        tg->cur.value += obj->cur.value;
        tg->pow += obj->pow;
        tg->ele += obj->ele;
        tg->activePow += obj->activePow;
    }
    tg->vol.value = box->loop[0].vol.value;
    //    tg->vol = averData(tg->vol.value, box->loopNum);
    bulidPf(tg);
}

void BUS_DpTg::lineTgObj(sDevData *box, int line, int loop)
{
    for(int i=0; i<line; ++i)
    {
        sObjData *tg = &(box->line[i]);
        memset(tg, 0, sizeof(sObjData));

        for(int j=0; j<loop; ++j) {
            sObjData *obj = &(box->loop[i+j*3]);
            tg->cur.value += obj->cur.value;
            tg->pow += obj->pow;
            tg->ele += obj->ele;
        }
        tg->vol.value = box->loop[i].vol.value;
        bulidPf(tg);
    }
}

void BUS_DpTg::LineTg(sDataPacket *box)
{
    int line=3, loop=3;
    if(box->dc == 0) {
        line = loop = 2;
        if((box->data.loopNum == 2) && (box->hz == 2)) {
            loop = 1;
        }
    }
    lineTgObj(&(box->data), line, loop);
}

void BUS_DpTg::tgBox(sDataPacket *box)
{
    if(box->offLine) {
        tgObj(&(box->data));
        LineTg(box);
    }

    int line = LINE_NUM;
    if(!box->dc) line = 2;
    box->data.lineNum = line;
}



void BUS_DpTg::tgBus(sBusData *bus)
{
    int line = LINE_NUM;
    if(!bus->dev[0].dc) line = 2;
    bus->dev[0].data.loopNum = line;

    for(int i=1; i<=bus->devNum; ++i) { // 插接箱统计
        tgBox(&(bus->dev[i]));
    }
}

void BUS_DpTg::tg()
{
    for(int i=0; i<BUS_NUM; ++i) {
        sBusData *bus = BusPacketSi::bulid()->getBus(i);
        tgBus(bus);
    }
}
