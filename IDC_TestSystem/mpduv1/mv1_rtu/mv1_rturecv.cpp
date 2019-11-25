/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1_rturecv.h"

MV1_RtuRecv::MV1_RtuRecv()
{

}

bool MV1_RtuRecv::rtuRecvCrc(uchar *buf, int len, ZM_sRtuRecv *msg)
{
    bool ret = true;
    int rtn = len-2; uchar *ptr = buf+rtn;

    msg->crc = (ptr[1]*256) + ptr[0]; // 获取校验码
    ushort crc = rtu_crc(buf, rtn);
    if(crc != msg->crc) {
        ret = false;
        qDebug() << "MV1_RtuRecv rtu recv crc Err!";
    }

    return ret;
}

int MV1_RtuRecv::rtuRecvHead(uchar *ptr,  ZM_sRtuRecv *pkt)
{
    pkt->addr = *(ptr++);// 从机地址码
    pkt->fn = *(ptr++);  /*功能码*/
    pkt->len = (*ptr); /*数据长度*/
    if(pkt->len > SERIAL_LEN) pkt->len = 0;

    return pkt->len;
}

uchar *MV1_RtuRecv::rtuRecvData(uchar *ptr, int num, uint *value)
{
    for(int i=0; i<num; ++i) {
        value[i] =  (*ptr) * 256 + *(ptr+1);  ptr += 2; // 读取电能高8位
        value[i] <<= 8; // 左移8位
        value[i] +=  (*ptr) * 256 + *(ptr+1);  ptr += 2; // 读取电能底8位
    }

    return ptr;
}

uchar *MV1_RtuRecv::rtuRecvData(uchar *ptr, int num, uint *value1,ushort *value2)
{
    for(int i=0; i<num; ++i) {
        value2[i] =  (*ptr) * 256 + *(ptr+1);  ptr += 2; // 读取电能高8位
        value2[i] <<= 8; // 左移8位
        value2[i] +=  (*ptr) * 256 + *(ptr+1);  ptr += 2; // 读取电能底8位
    }

    return ptr;
}

uchar *MV1_RtuRecv::rtuRecvData(uchar *ptr, int num, ushort *value)
{
    for(int i=0; i<num; ++i) {
        value[i] =  (*ptr) * 256 + *(ptr+1);  ptr += 2;
    }

    return ptr;
}

uchar *MV1_RtuRecv::rtuRecvData(uchar *ptr, int num, ushort *value1,uint *value2)
{
    for(int i=0; i<num; ++i) {
        value2[i] =  (*ptr) * 256 + *(ptr+1);  ptr += 2;
    }

    return ptr;
}


void MV1_RtuRecv::rtuLineData(uchar *buf, ZM_sObjData &pkt)
{
    int num = 3;
    buf = rtuRecvData(buf, num, pkt.vol.value);
    buf = rtuRecvData(buf, num, pkt.cur.value);
    buf = rtuRecvData(buf, num, (ushort *)(pkt.pow),pkt.pow);
    buf = rtuRecvData(buf, num, (uint *)(pkt.ele),pkt.ele);
    buf = rtuRecvData(buf, num, pkt.pf);
}

void MV1_RtuRecv::rtuOutputData(uchar *buf, ZM_sObjData &pkt)
{
    int num = 24;
    buf = rtuRecvData(buf, num, pkt.cur.value);
    buf = rtuRecvData(buf, num, (ushort *)(pkt.pow),pkt.pow);
}

void MV1_RtuRecv::rtuOutputEle(uchar *buf, ZM_sObjData &pkt)
{
    int num = 24;
    buf = rtuRecvData(buf, num, (uint *)(pkt.ele),pkt.ele);
    buf = rtuRecvData(buf, num, pkt.pf);
}

void MV1_RtuRecv::rtuEnvData(uchar *buf, ZM_sRtuPacket &pkt)
{
    int num = 2;
    buf = rtuRecvData(buf, num, pkt.env.tem.value );//pkt.tem.value
    buf = rtuRecvData(buf, num, pkt.env.hum.value );//pkt.hum.value
}

void MV1_RtuRecv::rtuLineThreshold(uchar *buf, ZM_sObjData &pkt)
{
    int num = 3;
    buf = rtuRecvData(buf, num, pkt.vol.min);
    buf = rtuRecvData(buf, num, pkt.vol.max);

    buf = rtuRecvData(buf, num, pkt.cur.min);
    buf = rtuRecvData(buf, num, pkt.cur.max);
}

void MV1_RtuRecv::rtuOutputThreshold(uchar *buf, ZM_sObjData &pkt)
{
    int num = 24;
    buf = rtuRecvData(buf, num, pkt.cur.min);
    buf = rtuRecvData(buf, num, pkt.cur.crMin);
    buf = rtuRecvData(buf, num, pkt.cur.crMax);
    buf = rtuRecvData(buf, num, pkt.cur.max);
}


void MV1_RtuRecv::rtuLineSw(uchar *buf, ZM_sObjData &pkt)
{
    int num = 3;
    buf = rtuRecvData(buf, num, pkt.sw);
    buf = rtuRecvData(buf, num, pkt.cur.crMin);
    buf = rtuRecvData(buf, num, pkt.cur.crMax);

    for(int i=0; i<num; ++i) pkt.sw[i] -= 1;
}

void MV1_RtuRecv::rtuOutputSw(uchar *buf, ZM_sObjData &pkt)
{
    int num = 3;
    ushort array[4] = {0};
    buf = rtuRecvData(buf, num, array);    

    int k=0;
    for(int i=0; i<num; ++i)
    {
        for(int j=0; j<8; ++j){
            ushort value = array[i] & (1 << (7-j) );
            if(value) pkt.sw[k++] = 1;
            else pkt.sw[k++] = 0;
        }
    }
}

void MV1_RtuRecv::rtuEnvThreshold(uchar *buf, ZM_sRtuPacket &pkt)
{
    int num = 2;
    for(int i=0; i<num; ++i) {
        buf = rtuRecvData(buf, 1, &(pkt.env.tem.min[i]));
        buf = rtuRecvData(buf, 1, &(pkt.env.hum.min[i]));
    }

    for(int i=0; i<num; ++i) {
        buf = rtuRecvData(buf, 1, &(pkt.env.tem.max[i]));
        buf = rtuRecvData(buf, 1, &(pkt.env.hum.max[i]));
    }
}

void MV1_RtuRecv::rtuDevAddr(uchar *buf, ZM_sRtuPacket &pkt)
{
    int num = 1;
    buf = rtuRecvData(buf, num, &(pkt.id));
    buf = rtuRecvData(buf, num, &(pkt.devSpec));
    buf = rtuRecvData(buf, num, &(pkt.br));

    memcpy(pkt.ip, buf, 8);
}

void MV1_RtuRecv::rtuLineNum(uchar *buf, ZM_sObjData &pkt)
{
    int num = 1;
    buf = rtuRecvData(buf, num, &(pkt.num));
}

bool MV1_RtuRecv::rtuRecvPacket(uchar *buf, int len, ZM_sRtuRecv *pkt)
{
    bool ret = true;
    int rtn = rtuRecvHead(buf,pkt);
    if(rtn < len)
    {
        buf += 3;
        switch (rtn/2) {
        case MV1_RtuReg_LineSize: // 相电压电流参数
            rtuLineData(buf, pkt->data.line);
            break;
        case MV1_RtuReg_OutputSize:
            rtuOutputData(buf, pkt->data.output);
            break;
        case MV1_RtuReg_OutputEleSize:
            rtuOutputEle(buf, pkt->data.output);
            break;
        case MV1_RtuReg_OutputSwSize:
            rtuOutputSw(buf, pkt->data.output);
            break;
        case MV1_RtuReg_EnvSize:
            rtuEnvData(buf, pkt->data);
            break;
        case MV1_RtuReg_LineThresholdSize:
            rtuLineThreshold(buf, pkt->data.line);
            break;
        case MV1_RtuReg_OutputThresholdSize:
            rtuOutputThreshold(buf, pkt->data.output);
            break;
        case MV1_RtuReg_LineSwSize:
            rtuLineSw(buf, pkt->data.line);
            break;
        case MV1_RtuReg_EnvThresholdSize:
            rtuEnvThreshold(buf, pkt->data);
            break;
        case MV1_RtuReg_DevAddrSize:
            rtuDevAddr(buf, pkt->data);
            break;
        case MV1_RtuReg_LineNumSize:
            rtuLineNum(buf, pkt->data.line);
            break;
        default:
            ret = false;
            qDebug() << "MV1_RtuRecv::rtuRecvPacket err" << rtn;
            break;
        }
    } else {
        ret = false;
    }

    return ret;
}

bool MV1_RtuRecv::recvPacket(uchar *buf, int len, ZM_sRtuRecv *pkt)
{
    bool ret = false;
    if((len > 2) && (len < 1024)) {
        ret =  rtuRecvCrc(buf, len, pkt);
        if(ret) {
            ret = rtuRecvPacket(buf, len, pkt);
        }
    } else {
        qDebug() << "MV1_RtuRecv recvPacket err" << ret;
    }

    return ret;
}
