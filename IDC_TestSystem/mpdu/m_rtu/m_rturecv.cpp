/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "m_rturecv.h"

M_RtuRecv::M_RtuRecv()
{

}

bool M_RtuRecv::rtuRecvCrc(uchar *buf, int len, M_sRtuRecv *msg)
{
    bool ret = true;
    int rtn = len-2; uchar *ptr = buf+rtn;

    msg->crc = (ptr[1]*256) + ptr[0]; // 获取校验码
    ushort crc = rtu_crc(buf, rtn);
    if(crc != msg->crc) {
        ret = false;
        qDebug() << "M_RtuRecv rtu recv crc Err!";
    }

    return ret;
}

int M_RtuRecv::rtuRecvHead(uchar *ptr,  M_sRtuRecv *pkt)
{
    pkt->addr = *(ptr++);// 从机地址码
    pkt->fn = *(ptr++);  /*功能码*/
    pkt->len = (*ptr); /*数据长度*/
    if(pkt->len > SERIAL_LEN) pkt->len = 0;

    return pkt->len;
}

uchar *M_RtuRecv::rtuRecvData(uchar *ptr, int num, uint *value)
{
    for(int i=0; i<num; ++i) {
        value[i] =  (*ptr) * 256 + *(ptr+1);  ptr += 2; // 读取电能高8位
        value[i] <<= 8; // 左移8位
        value[i] +=  (*ptr) * 256 + *(ptr+1);  ptr += 2; // 读取电能底8位
    }

    return ptr;
}

uchar *M_RtuRecv::rtuRecvData(uchar *ptr, int num, ushort *value)
{
    for(int i=0; i<num; ++i) {
        value[i] =  (*ptr) * 256 + *(ptr+1);  ptr += 2;
    }

    return ptr;
}


void M_RtuRecv::rtuLineData(uchar *buf, M_sObjData &pkt)
{
    int num = 3;
    buf = rtuRecvData(buf, num, pkt.vol.value);
    buf = rtuRecvData(buf, num, pkt.cur.value);
    buf = rtuRecvData(buf, num, pkt.pow);
    buf = rtuRecvData(buf, num, pkt.ele);
    buf = rtuRecvData(buf, num, pkt.pf);
}

void M_RtuRecv::rtuOutputData(uchar *buf, M_sObjData &pkt)
{
    int num = 24;
    buf = rtuRecvData(buf, num, pkt.cur.value);
    buf = rtuRecvData(buf, num, pkt.pow);
}

void M_RtuRecv::rtuOutputEle(uchar *buf, M_sObjData &pkt)
{
    int num = 24;
    buf = rtuRecvData(buf, num, pkt.ele);
    buf = rtuRecvData(buf, num, pkt.pf);
}

void M_RtuRecv::rtuEnvData(uchar *buf, M_sRtuPacket &pkt)
{
    int num = 2;
    buf = rtuRecvData(buf, num, pkt.tem.value);
    buf = rtuRecvData(buf, num, pkt.hum.value);
}

void M_RtuRecv::rtuLineThreshold(uchar *buf, M_sObjData &pkt)
{
    int num = 3;
    buf = rtuRecvData(buf, num, pkt.vol.min);
    buf = rtuRecvData(buf, num, pkt.vol.max);

    buf = rtuRecvData(buf, num, pkt.cur.min);
    buf = rtuRecvData(buf, num, pkt.cur.max);
}

void M_RtuRecv::rtuOutputThreshold(uchar *buf, M_sObjData &pkt)
{
    int num = 24;
    buf = rtuRecvData(buf, num, pkt.cur.min);
    buf = rtuRecvData(buf, num, pkt.cur.max);
}

void M_RtuRecv::rtuLineSw(uchar *buf, M_sObjData &pkt)
{
    int num = 3;
    buf = rtuRecvData(buf, num, pkt.sw);
}

void M_RtuRecv::rtuOutputSw(uchar *buf, M_sRtuPacket &pkt)
{
    int num = 24;
    buf = rtuRecvData(buf, num, pkt.output.sw);
    buf = rtuRecvData(buf, num, pkt.output.delay);

    rtuRecvData(buf, 1, &(pkt.version));
}

void M_RtuRecv::rtuEnvThreshold(uchar *buf, M_sRtuPacket &pkt)
{
    int num = 3;
    buf = rtuRecvData(buf, num, pkt.tem.min);
    buf = rtuRecvData(buf, num, pkt.tem.max);

    buf = rtuRecvData(buf, num, pkt.hum.min);
    buf = rtuRecvData(buf, num, pkt.hum.max);
}

void M_RtuRecv::rtuDevAddr(uchar *buf, M_sRtuPacket &pkt)
{
    int num = 1;
    buf = rtuRecvData(buf, num, &(pkt.id));
    buf = rtuRecvData(buf, num, &(pkt.devSpec));
    buf = rtuRecvData(buf, num, &(pkt.br));

    memcpy(pkt.ip, buf, 8);
}

void M_RtuRecv::rtuLineNum(uchar *buf, M_sObjData &pkt)
{
    int num = 1;
    buf = rtuRecvData(buf, num, &(pkt.num));
}

bool M_RtuRecv::rtuRecvPacket(uchar *buf, int len, M_sRtuRecv *pkt)
{
    bool ret = true;
    int rtn = rtuRecvHead(buf,pkt);
    if(rtn < len)
    {
        switch (rtn/2) {
        case M_RtuReg_LineSize: // 相电压电流参数
            rtuLineData(buf, pkt->data.line);
            break;
        case M_RtuReg_OutputSize:
            rtuOutputData(buf, pkt->data.output);
            break;
        case M_RtuReg_OutputEleSize:
            rtuOutputEle(buf, pkt->data.output);
            break;
        case M_RtuReg_EnvSize:
            rtuEnvData(buf, pkt->data);
            break;
        case M_RtuReg_LineThresholdSize:
            rtuLineThreshold(buf, pkt->data.line);
            break;
        case M_RtuReg_OutputThresholdSize:
            rtuLineThreshold(buf, pkt->data.output);
            break;
        case M_RtuReg_LineSwSize:
            rtuLineSw(buf, pkt->data.line);
            break;
        case M_RtuReg_OutputSwSize:
            rtuOutputSw(buf, pkt->data);
            break;
        case M_RtuReg_EnvThresholdSize:
            rtuEnvThreshold(buf, pkt->data);
            break;
        case M_RtuReg_DevAddrSize:
            rtuDevAddr(buf, pkt->data);
            break;
        case M_RtuReg_LineNumSize:
            rtuLineNum(buf, pkt->data.line);
            break;
        default:
            ret = false;
            qDebug() << "M_RtuRecv::rtuRecvPacket err" << rtn;
            break;
        }
    } else {
        ret = false;
    }

    return ret;
}

bool M_RtuRecv::recvPacket(uchar *buf, int len, M_sRtuRecv *pkt)
{
    bool ret = false;
    if((len > 2) && (len < 1024)) {
        ret =  rtuRecvCrc(buf, len, pkt);
        if(ret) {
            ret = rtuRecvPacket(buf, len, pkt);
        }
    } else {
        qDebug() << "M_RtuRecv recvPacket err" << ret;
    }

    return ret;
}
