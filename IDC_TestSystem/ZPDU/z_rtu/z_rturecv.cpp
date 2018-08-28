/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "z_rturecv.h"

Z_RtuRecv::Z_RtuRecv()
{

}


bool Z_RtuRecv::rtuRecvCrc(uchar *buf, int len, Z_sRtuRecv *msg)
{
    bool ret = true;
    int rtn = len-2; uchar *ptr = buf+rtn;

    msg->crc = (ptr[1]*256) + ptr[0]; // 获取校验码
    ushort crc = rtu_crc(buf, rtn);
    if(crc != msg->crc) {
        ret = false;
        qDebug() << "Z_RtuRecv rtu recv crc Err!";
    }

    return ret;
}

int Z_RtuRecv::rtuRecvHead(uchar *ptr,  Z_sRtuRecv *pkt)
{
    pkt->addr = *(ptr++);// 从机地址码
    pkt->fn = *(ptr++);  /*功能码*/
    pkt->len = (*ptr); /*数据长度*/
    if(pkt->len > SERIAL_LEN) pkt->len = 0;

    return pkt->len;
}

uchar *Z_RtuRecv::rtuRecvData(uchar *ptr, int num, uint *value)
{
    for(int i=0; i<num/4; ++i) {
        value[i] =  (*ptr) * 256 + *(ptr+1);  ptr += 2; // 读取电能高8位
        value[i] <<= 8; // 左移8位
        value[i] +=  (*ptr) * 256 + *(ptr+1);  ptr += 2; // 读取电能底8位
    }

    return ptr;
}

uchar *Z_RtuRecv::rtuRecvData(uchar *ptr, int num, ushort *value)
{
    for(int i=0; i<num/2; ++i) {
        value[i] =  (*ptr) * 256 + *(ptr+1);  ptr += 2;
    }

    return ptr;
}

uchar *Z_RtuRecv::rtuRecvData(uchar *ptr, int num, uchar *value)
{
    for(int i=0; i<num; ++i) {
        value[i] =  (*ptr) * 256 + *(ptr+1);  ptr += 2;
    }

    return ptr;
}

void Z_RtuRecv::devTypeData(uchar *buf, int len, Z_sRtuPacket &pkt)
{
    ushort array[3] = {0};
    rtuRecvData(buf, len, array);

    int value = array[0], line=3, loop=6;
    if((value<5) || ((value>8) &&(value<13))) line = 1;

    if(value < 5) loop = 2;
    else if(value < 9) loop = 3;
    else if(value < 13) loop = 4;

    pkt.line.num = line;
    pkt.loop.num = loop;
    pkt.devSpec = value%4;
}

void Z_RtuRecv::devIpAddr(uchar *buf, int len, Z_sRtuPacket &pkt)
{
    uchar array[20] = {0};
    rtuRecvData(buf, len, array);
    sprintf(pkt.mac, "%d.%d.%d.%d", array[1], array[0], array[3], array[2]);
}

void Z_RtuRecv::devMac(uchar *buf, int len, Z_sRtuPacket &pkt)
{
    uchar array[30] = {0};
    rtuRecvData(buf, len, array);
    sprintf(pkt.mac, "%02x:%02x:%02x:%02x:%02x:%02x", array[0], array[1], array[2], array[3], array[4], array[5]);
}


bool Z_RtuRecv::rtuRecvPacket(uchar *buf, int len, ushort reg, Z_sRtuPacket &pkt)
{
    bool ret = true;
    ushort *ptrShort = nullptr;

    switch (reg) {
    case Z_RtuReg_DevType: devTypeData(buf, len, pkt); break;
    case Z_RtuReg_DevIP: devIpAddr(buf, len, pkt); break;
    case Z_RtuReg_DevMac: devMac(buf, len, pkt); break;
    case Z_RtuReg_OutputNum: ptrShort = &(pkt.output.num); break;
    case Z_RtuReg_OutputSw: ptrShort = pkt.output.sw; break;

    case Z_RtuReg_LineCur: ptrShort = pkt.line.cur.value; break;
    case Z_RtuReg_LineCurMin: ptrShort = pkt.line.cur.min; break;
    case Z_RtuReg_LineCurMax: ptrShort = pkt.line.cur.max; break;
    case Z_RtuReg_LineCurCrMin: ptrShort = pkt.line.cur.crMin; break;
    case Z_RtuReg_LineCurCrMax: ptrShort = pkt.line.cur.crMax; break;

    case Z_RtuReg_LineVol: ptrShort = pkt.line.vol.value; break;
    case Z_RtuReg_LineVolMin: ptrShort = pkt.line.vol.min; break;
    case Z_RtuReg_LineVolMax: ptrShort = pkt.line.vol.max; break;
    case Z_RtuReg_LineVolCrMin: ptrShort = pkt.line.vol.crMin; break;
    case Z_RtuReg_LineVolCrMax: ptrShort = pkt.line.vol.crMax; break;

    case Z_RtuReg_LinePow: ptrShort = pkt.line.pow; break;
    case Z_RtuReg_LinePF: ptrShort = pkt.line.pf; break;
    case Z_RtuReg_LineEle: ptrShort = pkt.line.ele; break;

    case Z_RtuReg_LoopCur: ptrShort = pkt.loop.cur.value; break;
    case Z_RtuReg_LoopCurMin: ptrShort = pkt.loop.cur.min; break;
    case Z_RtuReg_LoopCurMax: ptrShort = pkt.loop.cur.max; break;
    case Z_RtuReg_LoopCurCrMin: ptrShort = pkt.loop.cur.crMin; break;
    case Z_RtuReg_LoopCurCrMax: ptrShort = pkt.loop.cur.crMax; break;
    case Z_RtuReg_LoopVol: ptrShort = pkt.loop.vol.value; break;
    case Z_RtuReg_LoopEle: ptrShort = pkt.loop.ele; break;

    case Z_RtuReg_OutputCur: ptrShort = pkt.output.cur.value; break;
    case Z_RtuReg_OutputCurMin: ptrShort = pkt.output.cur.min; break;
    case Z_RtuReg_OutputCurMax: ptrShort = pkt.output.cur.max; break;
    case Z_RtuReg_OutputCurCrMin: ptrShort = pkt.output.cur.crMin; break;
    case Z_RtuReg_OutputCurCrMax: ptrShort = pkt.output.cur.crMax; break;
    case Z_RtuReg_OutputPF: ptrShort = pkt.output.pf; break;
    case Z_RtuReg_OutputEle: ptrShort = pkt.output.ele; break;

    case Z_RtuReg_TemData: ptrShort = pkt.env.tem.value; break;
    case Z_RtuReg_TemMin: ptrShort = pkt.env.tem.min; break;
    case Z_RtuReg_TemMax: ptrShort = pkt.env.tem.max; break;
    case Z_RtuReg_TemCrMin: ptrShort = pkt.env.tem.crMin; break;
    case Z_RtuReg_TemCrMax: ptrShort = pkt.env.tem.crMax; break;

    case Z_RtuReg_HumData: ptrShort = pkt.env.hum.value; break;
    case Z_RtuReg_HumMin: ptrShort = pkt.env.hum.min; break;
    case Z_RtuReg_HumMax: ptrShort = pkt.env.hum.max; break;
    case Z_RtuReg_HumCrMin: ptrShort = pkt.env.hum.crMin; break;
    case Z_RtuReg_HumCrMax: ptrShort = pkt.env.hum.crMax; break;

    case Z_RtuReg_DoorData: ptrShort = pkt.env.door; break;
    case Z_RtuReg_WaterData: ptrShort = pkt.env.water; break;
    case Z_RtuReg_SmokeData: ptrShort = pkt.env.smoke; break;

    default:
        ret = false;
        qDebug() << "Z_RtuRecv::rtuRecvPacket err" << reg;
        break;
    }

    if(ptrShort) rtuRecvData(buf, len, ptrShort);

    return ret;
}

bool Z_RtuRecv::recvPacket(uchar *buf, int len, ushort reg, Z_sRtuRecv *pkt)
{
    bool ret = false;
    if((len > 5) && (len < 1024)) {
        ret =  rtuRecvCrc(buf, len, pkt);
        if(ret) {
            int rtn = rtuRecvHead(buf,pkt);
            if(rtn < len)
            {
                buf += 3;
                ret = rtuRecvPacket(buf, rtn, reg, pkt->data);
            }
        }
    } else {
        qDebug() << "Z_RtuRecv recvPacket err" << ret;
    }

    return ret;
}
