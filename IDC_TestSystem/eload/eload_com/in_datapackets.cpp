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
    int tem = data[1].value - data[2].value;
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
