﻿#include "rtutrans.h"

RtuTrans::RtuTrans(QObject *parent)
{

}

bool RtuTrans::setValue(const sRtuSetCmd &cmd)
{
    return sentSetCmd(cmd.addr, cmd.reg, cmd.value, 5);
}


void RtuTrans::getAlarm(sDataUnit &data)
{
    if((data.value < data.min) || (data.value > data.max)) {
        if(data.alarm == 0)
            data.alarm = 1;
    } else {
        data.alarm = 0;
    }

    if((data.value < data.crMin) || (data.value > data.crMax)) {
        if(data.crAlarm == 0)
            data.crAlarm = 1;
    } else {
        data.crAlarm = 0;
    }
}

void RtuTrans::dataUnit(int i, ZM_sDataUnit &rtu, sDataUnit &data, int rate)
{
    //qDebug()<<i<<data.value<< rtu.value[i] / rate;
    data.value = rtu.value[i] / rate;
    data.min = rtu.min[i] / rate;
    data.max = rtu.max[i] / rate;

    data.crMin = rtu.crMin[i] / rate;
    data.crMax = rtu.crMax[i] / rate;

    getAlarm(data);
}

void RtuTrans::devObjData(ZM_sObjData &rtuData, int i, sObjData &data , bool flag)
{
    data.id = i;
    dataUnit(i, rtuData.vol, data.vol, 1);
    dataUnit(i, rtuData.cur, data.cur, 1);
    data.ele = rtuData.ele[i];
    data.activePow = (data.vol.value>1000&&data.vol.value<3000?data.vol.value/10:data.vol.value) * data.cur.value / 100;
    data.pf = rtuData.pf[i];
    data.sw = rtuData.sw[i];

    if(flag)
    {
        if(data.sw != 1)
        {
            if(data.vol.value)
            {
                data.sw = 1;
            }
            else  data.sw = 0;
        }
    }
    if(rtuData.pow[i] > 0) {
        data.pow = rtuData.pow[i] / 1000;
    } else if(data.pf){
        data.pow = (data.vol.value>1000&&data.vol.value<3000?data.vol.value/10:data.vol.value) * data.cur.value * data.pf / (100*100.0);
    }
}

void RtuTrans::envData(ZM_sEnv &rtuData, sEnvData &data)
{
    data.envNum = 2;

    for(int i=0; i<data.envNum; ++i) {
        dataUnit(i, rtuData.tem, data.tem[i]);
        dataUnit(i, rtuData.hum, data.hum[i]);

        data.door[i] = rtuData.door[i];
        data.water[i] = rtuData.water[i];
        data.smoke[i] = rtuData.smoke[i];
    }
}

void RtuTrans::devData(ZM_sRtuPacket &rtuData, sDevData &data)
{
    int num = rtuData.line.num = data.lineNum;
    for(int i=0; i<num; ++i) {
        devObjData(rtuData.line, i, data.line[i] , true);
    }

    num = rtuData.loop.num = data.loopNum;
    for(int i=0; i<num; ++i) {
        //devObjData(rtuData.loop, i, data.loop[i] , data.line[i/2].sw);//RTU可能读不到
        data.loop[i].vol.alarm = data.loop[i].vol.crAlarm = 0;
    }

    num = data.outputNum = rtuData.output.num;
    for(int i=0; i<num; ++i) {
        data.output[i].vol.value = rtuData.output.vol.value[i] = data.line[0].vol.value? data.line[0].vol.value : 220;
        devObjData(rtuData.output, i, data.output[i] ,false);
        data.output[i].vol.alarm = data.output[i].vol.crAlarm = 0;
    }

    envData(rtuData.env, data.env);
}

void RtuTrans::devDataPacket(ZM_sRtuRecv *pkt, sDataPacket *packet)
{
    packet->id = pkt->addr;
    packet->offLine = pkt->offLine;
    packet->br = pkt->data.br;
    packet->version = pkt->data.version;
    packet->devSpec = pkt->data.devSpec;
    strcpy(packet->ip, pkt->data.ip);
    strcpy(packet->mac, pkt->data.mac);

    devData(pkt->data, packet->data);
}

