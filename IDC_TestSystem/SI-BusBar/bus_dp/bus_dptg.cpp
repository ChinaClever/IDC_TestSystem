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

void BUS_DpTg::bulidPf(BUS_sObjUnit *unit)
{
    unit->apPow = unit->vol.value * unit->cur.value;

    if(unit->pow > unit->apPow) {
        unit->pow = unit->apPow;
    }

    if(unit->apPow > 0) {
        unit->pf = (unit->pow * 100.0 / unit->apPow);
        if(unit->pf > 99) unit->pf = 99;
    } else {
        unit->pf = 0;
    }

    //  tg->pf = averData(obj->pf);
}

void BUS_DpTg::tgObj(sBoxData *box)
{
    BUS_sObjUnit *tg = &(box->tg);
    memset(tg, 0, sizeof(BUS_sObjUnit));
    for(int i=0; i<box->loopNum; ++i)
    {
        BUS_sObjUnit *obj = &(box->loop[i]);
        tg->cur.value += obj->cur.value;
        tg->pow += obj->pow;
        tg->ele += obj->ele;
        tg->apPow += obj->apPow;
    }
    tg->vol.value = box->loop[0].vol.value;
    //    tg->vol = averData(tg->vol.value, box->loopNum);
    bulidPf(tg);
}

void BUS_DpTg::lineTgObj(sBoxData *box, int line, int loop)
{
    for(int i=0; i<line; ++i)
    {
        BUS_sObjUnit *tg = &(box->line[i]);
        memset(tg, 0, sizeof(BUS_sObjUnit));

        for(int j=0; j<loop; ++j) {
            BUS_sObjUnit *obj = &(box->loop[i+j*3]);
            tg->cur.value += obj->cur.value;
            tg->pow += obj->pow;
            tg->ele += obj->ele;
        }
        tg->vol.value = box->loop[i].vol.value;
        bulidPf(tg);
    }
}

void BUS_DpTg::LineTg(sBoxData *box)
{
    int line=3, loop=3;
    if(box->dc == 0) {
        line = loop = 2;
        if((box->loopNum == 2) && (box->rate == 2)) {
            loop = 1;
        }
    }
    lineTgObj(box, line, loop);
}

void BUS_DpTg::tgBox(sBoxData *box)
{
    if(box->offLine) {
        tgObj(box);
        LineTg(box);
    }
}

void BUS_DpTg::tgBus(sBusData *bus)
{
    for(int i=0; i<=bus->boxNum; ++i) { // 插接箱统计
        tgBox(&(bus->box[i]));
    }
}

void BUS_DpTg::tg()
{
    for(int i=0; i<BUS_NUM; ++i) {
        sBusData *bus = BusPacketSi::bulid()->getBus(i);
        tgBus(bus);
    }
}
