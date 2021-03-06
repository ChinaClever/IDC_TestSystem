﻿/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ip_rturecv.h"


/**
  * 功　能：长度 校验
  * 入口参数：buf -> 缓冲区  len -> 长度
  * 返回值：0 正确
  */
static int rtu_recv_len(uchar *buf, int len)
{
    int ret = 0;

    if(len < IP_RTU_ONE_LEN) {
        ret = -1;
        qDebug() << "rtu recv Err: len too short!!" << len;
    } else if(len > IP_RTU_THREE_LEN*2 + 7) {
        ret = -2;
        qDebug() << "rtu recv Err: len too long!!" << len;
    } else {
        len = buf[2];
        if(len == IP_RTU_ONE_LEN*2) {
            ret = 1;
        } else if (len == IP_RTU_THREE_LEN*2) {
            ret = 3;
        } else  {
            ret = -3;
            qDebug() << "rtu recv len Err!!" << len  ;
            len = 0;
        }
    }

    return ret;
}


/**
  * 功　能：读取数据包头部
  * 入口参数：ptr -> 缓冲区
  * 出口参数：pkt -> 结构体
  * 返回值：0 正确
  */
static int rtu_recv_head(uchar *ptr,  IP_Rtu_Recv *pkt)
{
    pkt->addr = *(ptr++);// 从机地址码
    pkt->fn = *(ptr++);  /*功能码*/
    pkt->len = (*ptr); /*数据长度*/
    if(pkt->len > SERIAL_LEN) pkt->len = 0;

    return 3;
}


static uchar *rtu_recv_data(uchar *ptr, int line, uint *value)
{
    for(int i=0; i<line; ++i) {
        value[i] =  (*ptr) * 256 + *(ptr+1);  ptr += 2; // 读取电能高8位
        value[i] <<= 8; // 左移8位
        value[i] +=  (*ptr) * 256 + *(ptr+1);  ptr += 2; // 读取电能底8位
    }

    return ptr;
}

static uchar *rtu_recv_data(uchar *ptr, int line, ushort *value)
{
    for(int i=0; i<line; ++i) {
        value[i] =  (*ptr) * 256 + *(ptr+1);  ptr += 2;
    }

    return ptr;
}

static uchar *rtu_recv_unit(uchar *ptr, int line, IP_sDataUnit &unit)
{
    for(int i=0; i<line; ++i) {
        ptr = rtu_recv_data(ptr, 1, &unit.min[i]);
        ptr = rtu_recv_data(ptr, 1, &unit.max[i]);
    }

    return ptr;
}

static uchar *rtu_recv_data(uchar *ptr, int line, uchar *value)
{
    for(int i=0; i<line; ++i) {
        value[i] =  *(ptr++); // 读取电压
    }

    return ptr;
}

static uchar *rtu_recv_data(uchar *ptr, int line, uchar *value1,ushort *value2)
{
    for(int i=0; i<line; ++i) {
        value1[i] =  (*ptr) * 256 + *(ptr+1);  ptr += 2;
    }

    return ptr;
}

static uchar *rtu_recv_data(uchar *ptr, int line, ushort *value1,uchar *value2)
{
    for(int i=0; i<line; ++i) {
        value1[i] = *(ptr+1)==2?1:0;  ptr += 2;
    }

    return ptr;
}

/**
  * 功　能：读取电参数 数据
  * 入口参数：ptr -> 缓冲区
  * 出口参数：pkt -> 结构体
  * 返回值：12 正确
  */
static int rtu_recv_data(uchar *ptr, IP_RtuRecvLine *msg)
{
    uchar *ret = ptr;

    int line = IP_LINE_NUM;
    ptr =  rtu_recv_data(ptr, line, msg->vol.value);
    ptr =  rtu_recv_data(ptr, line, msg->cur.value);
    ptr =  rtu_recv_data(ptr, line, msg->pow);
    ptr =  rtu_recv_data(ptr, line, msg->hz);
    ptr =  rtu_recv_data(ptr, line, msg->ele);
    ptr =  rtu_recv_data(ptr, 1, msg->tem.value);
    ptr =  rtu_recv_data(ptr, 1, msg->hum.value);
    ptr =  rtu_recv_unit(ptr, line, msg->vol);
    ptr =  rtu_recv_unit(ptr, line, msg->cur);
    ptr =  rtu_recv_unit(ptr, 1, msg->tem);
    ptr =  rtu_recv_unit(ptr, 1, msg->hum);

    ptr += (2*2*line + 2 + 2);
//    ptr =  rtu_recv_data(ptr, line, msg->vol.alarm);
//    ptr =  rtu_recv_data(ptr, line, msg->cur.alarm);
//    ptr =  rtu_recv_data(ptr, 1, msg->tem.alarm);
//    ptr =  rtu_recv_data(ptr, 1, msg->hum.alarm);

    ptr =  rtu_recv_data(ptr, 2, msg->sw,(uchar*)msg->sw); // 开关状态
    ptr =  rtu_recv_data(ptr, 1, &(msg->lineNum));
    ptr =  rtu_recv_data(ptr, 1, &(msg->version));
    ptr =  rtu_recv_data(ptr, 1, &(msg->br));
    ptr =  rtu_recv_data(ptr, 1, &(msg->reserve));

    return ptr-ret;
}


/**
  * 功　能：读取电参数 数据
  * 入口参数：ptr -> 缓冲区
  * 出口参数：pkt -> 结构体
  * 返回值：12 正确
  */
static int rtu_recv_dataV3(uchar *ptr, IP_RtuRecvLine *msg)
{
    uchar *ret = ptr;

    int line = IP_LINE_NUM;
    ptr =  rtu_recv_data(ptr, line, msg->vol.value);
    ptr =  rtu_recv_data(ptr, line, msg->cur.value);
    ptr =  rtu_recv_data(ptr, line, msg->pf,(ushort*)msg->pf);
    ptr =  rtu_recv_data(ptr, line, msg->pow);
    ptr =  rtu_recv_data(ptr, line, msg->activePow);
    ptr =  rtu_recv_data(ptr, line, msg->ele);
    ptr =  rtu_recv_data(ptr, 1, msg->hz);
    ptr =  rtu_recv_data(ptr, line, msg->sw,(uchar*)msg->sw); // 开关状态
    ptr =  rtu_recv_data(ptr, 1, msg->tem.value);
    ptr =  rtu_recv_data(ptr, 1, msg->hum.value);
    ptr =  rtu_recv_unit(ptr, line, msg->vol);
    ptr =  rtu_recv_unit(ptr, line, msg->cur);
    ptr =  rtu_recv_unit(ptr, 1, msg->tem);
    ptr =  rtu_recv_unit(ptr, 1, msg->hum);

    ptr += (2*2*line + 2 + 2);
//    ptr =  rtu_recv_data(ptr, line, msg->vol.alarm);
//    ptr =  rtu_recv_data(ptr, line, msg->cur.alarm);
//    ptr =  rtu_recv_data(ptr, 1, msg->tem.alarm);
//    ptr =  rtu_recv_data(ptr, 1, msg->hum.alarm);

    ptr =  rtu_recv_data(ptr, 1, &(msg->lineNum));
    ptr =  rtu_recv_data(ptr, 1, &(msg->version));
    ptr =  rtu_recv_data(ptr, 1, &(msg->br));
    ptr =  rtu_recv_data(ptr, 8, msg->ip);
    ptr =  rtu_recv_data(ptr, 1, &(msg->reserve));

    return ptr-ret;
}

/**
  * 功　能：检验码 数据
  * 入口参数：buf -> 缓冲区
  * 出口参数：pkt -> 结构体
  * 返回值：true
  */
static bool rtu_recv_crc(uchar *buf, int len, IP_Rtu_Recv *msg)
{
    bool ret = true;
    int rtn = len-2; uchar *ptr = buf+rtn;

    msg->crc = (ptr[1]*256) + ptr[0]; // 获取校验码
    ushort crc = rtu_crc(buf, rtn);
    if(crc != msg->crc) {
        ret = false;
        qDebug() << "rtu recv crc Err!";
    }

    return ret;
}

/**
  * 功　能：还原数据包
  * 入口参数：buf -> 缓冲区   len -> 数据长度
  * 出口参数：pkt -> 结构体
  * 返回值：true
  */
static bool rtu_recv_packet(uchar *buf, int len, IP_Rtu_Recv *pkt)
{
    bool ret = false;

    int line = rtu_recv_len(buf, len);
    if(line > 0) {
        uchar *ptr=buf;
        ptr += rtu_recv_head(ptr, pkt);
        if(line > 1) {
            ptr += rtu_recv_dataV3(ptr, &(pkt->data));
        } else {
            ptr += rtu_recv_data(ptr, &(pkt->data));
        }

        pkt->v = line;
        ret = rtu_recv_crc(buf, len, pkt);
    }

    return ret;
}


bool IP_RtuRecv::recvPacket(uchar *buf, int len, IP_Rtu_Recv *pkt)
{
    bool ret = false;
    if((len > 2) && (len < 1024))
        ret = rtu_recv_packet(buf, len, pkt);
    else
        qDebug() << "IP_RtuRecv recvPacket err" << ret;

    return ret;
}

