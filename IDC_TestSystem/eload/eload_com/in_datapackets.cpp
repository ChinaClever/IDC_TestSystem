/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "in_datapackets.h"

IN_DataPackets::IN_DataPackets()
{
    packets = new sDevPackets();
    memset(packets, 0, sizeof(sDevPackets));
}

IN_DataPackets *IN_DataPackets::bulid()
{
    static IN_DataPackets* sington = nullptr;
    if(sington == nullptr)
        sington = new IN_DataPackets();
    return sington;
}

sDataPacket *IN_DataPackets::getDev(int num)
{
    return &(packets->dev[num]);
}

int IN_DataPackets::getTemRise(int id)
{
    sDataUnit *data = getDev(id)->data.env.tem;
    int tem = data[2].value - data[1].value;
    if(tem<0) tem = 0 - tem;

    return tem;
}


int IN_DataPackets::getTgValue(int mode)
{
    int ret = 0, value;
    for(int i=0; i<=packets->devNum; i++)
    {
        sDevData *data = &(getDev(i)->data);
        for(int j=0; j<data->inputNum; j++)
        {
            switch (mode) {
            case 1:
                value = data->input[j].vol.value;
                if(value > ret) ret = value;
                break;
            case 2:
                ret += data->input[j].cur.value;
                break;

            case 3:
                ret += data->input[j].pow;
                break;

            case 4:
                ret += data->input[j].ele;
                break;

            case 5:
                value = getDev(i)->hz;
                if(value > ret) ret = value;
                break;

            case 6:
                if(j>0) break;
                value = data->env.tem[j].value;
                if(value > ret) ret = value;
                break;
            default:
                break;
            }

        }
    }

    return ret;
}

int IN_DataPackets::getTgValueByIndex(int mode,int index)
{
    int ret = 0, value;
    if( index <= packets->devNum )
    {
        sDevData *data = &(getDev(index)->data);
        for(int j=0; j<data->inputNum; j++)
        {
            switch (mode) {
            case 1:
                value = data->input[j].vol.value;
                if(value > ret) ret = value;
                break;
            case 2:
                ret += data->input[j].cur.value;
                break;

            case 3:
                ret += data->input[j].pow;
                break;

            case 4:
                ret += data->input[j].ele;
                break;

            case 5:
                value = getDev(index)->hz;
                if(value > ret) ret = value;
                break;

            case 6:
                if(j>0) break;
                value = data->env.tem[j].value;
                if(value > ret) ret = value;
                break;
            default:
                break;
            }

        }
    }

    return ret;
}

int IN_DataPackets::getLineVol(int id)
{
    sDevData *data = &(getDev(1)->data);
    return data->input[id+1].vol.value;
}

sObjData *IN_DataPackets::getObjData(int id)
{
    sDevData *data = &(getDev(id/8)->data);
    return &(data->input[id%8]);
}


int IN_DataPackets::getTgCur(int s, int e)
{
    int ret = 0;
    for(int i=s; i<e; ++i) {
        sObjData *obj = getObjData(i+8);
        ret += obj->cur.value;
    }
    return ret;
}

int IN_DataPackets::getApPow(int i)
{
    i += 8;
    int  expect = getObjData(i)->pow;
    if(getObjData(i)->pf != 0)
        expect = (double)getObjData(i)->pow/getObjData(i)->pf*COM_RATE_CUR2;

    return expect;

}

int IN_DataPackets::getTgPow(int i , int addr ,bool powOrActivePowFlag)
{
    int expect = 0; i += 8;
    if(getObjData(i)->pf != 0  && !powOrActivePowFlag)
        expect = (double)getTgValueByIndex(3 ,addr)/getObjData(i)->pf*COM_RATE_CUR2;
    else
        expect = getTgValueByIndex(3 ,addr);

    return expect;
}

int IN_DataPackets::getTgPowByStratAndEnd(int s , int e)
{
    int sumPow = 0;
    for(int i = s ; i < e ; i++)
        sumPow += getObjData(i+8)->pow;
    return sumPow;
}
