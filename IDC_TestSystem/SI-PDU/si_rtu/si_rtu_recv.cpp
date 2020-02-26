/*
 * ETU接收数据
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "si_rtu_recv.h"


/**
  * 功　能：长度 校验
  * 入口参数：buf -> 缓冲区  len -> 长度
  * 返回值：0 正确
  */
static int rtu_recv_len(uchar *buf, int len)
{
    int ret = 0;

    if(len < SI_RTU_ONE_LEN) {
        ret = -1;
        qDebug() << "rtu recv Err: len too short!!" << len;
    } else if(len > SI_RTU_THREE_LEN + 7) {
        ret = -2;
        qDebug() << "rtu recv Err: len too long!!" << len;
    } else {
        len = buf[2]*256 + buf[3];
        if(len == SI_RTU_ONE_LEN) {
            ret = 1;
        } else if (len == SI_RTU_THREE_LEN) {
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
static int rtu_recv_head(uchar *ptr,  SI_Rtu_Recv *pkt)
{
    pkt->addr = *(ptr++);// 从机地址码
    pkt->fn = *(ptr++);  /*功能码*/
    pkt->len = (*ptr) * 256 + *(ptr+1); /*数据长度*/
    if(pkt->len > SERIAL_LEN) pkt->len = 0;

    return 4;
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

static uchar *rtu_recv_unit(uchar *ptr, int line, SI_sDataUnit &unit)
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

static void rtu_recv_alarm(SI_sDataUnit &unit, int line)
{
    for(int i=0; i<line; ++i)
    {
        if((unit.value[i] > unit.max[i]) || (unit.value[i] < unit.min[i])) {
            if(unit.alarm[i] == 0)
                unit.alarm[i] = 1;
        } else {
            unit.alarm[i] = 0;
        }
    }
}


/**
  * 功　能：读取电参数 数据
  * 入口参数：ptr -> 缓冲区
  * 出口参数：pkt -> 结构体
  * 返回值：12 正确
  */
static int rtu_recv_data(uchar *ptr, int line, SI_RtuRecvLine *msg)
{
    int ret = SI_RTU_ONE_LEN;

    ptr =  rtu_recv_data(ptr, line, msg->vol.value);
    ptr =  rtu_recv_data(ptr, line, msg->cur.value);
    ptr =  rtu_recv_data(ptr, line, msg->pow);
    ptr =  rtu_recv_data(ptr, line, msg->ele);

    ptr =  rtu_recv_unit(ptr, line, msg->vol);
    rtu_recv_alarm(msg->vol, line);

    ptr =  rtu_recv_unit(ptr, line, msg->cur);
    rtu_recv_alarm(msg->cur, line);

    msg->tem.value[0] =  *(ptr++);// 温度
    msg->hum.value[0] =  *(ptr++);// 湿度
    if(line > 1) {
        msg->tem.max[0] =  *(ptr++);
        msg->tem.min[0] =  *(ptr++);
        rtu_recv_alarm(msg->tem, line);

        msg->hum.max[0] =  *(ptr++);
        msg->hum.min[0] =  *(ptr++);
        rtu_recv_alarm(msg->hum, line);

        msg->lineNum =  *(ptr++);
    }

    msg->br =  *(ptr++); // 波特率
    ptr =  rtu_recv_data(ptr, line, msg->activePow);
    ptr =  rtu_recv_data(ptr, line, msg->pf); // 功率因数
    ptr =  rtu_recv_data(ptr, line, msg->sw); // 开关状态

    if(line == 1) {
        msg->lineNum =  *(ptr++);
    } else {
        ret = SI_RTU_THREE_LEN;
    }
    msg->lineNum = line;

    return ret;
}


/**
  * 功　能：检验码 数据
  * 入口参数：buf -> 缓冲区
  * 出口参数：pkt -> 结构体
  * 返回值：true
  */
static bool rtu_recv_crc(uchar *buf, int len, SI_Rtu_Recv *msg)
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
static bool rtu_recv_packet(uchar *buf, int len, SI_Rtu_Recv *pkt)
{
    bool ret = false;

    int line = rtu_recv_len(buf, len);
    if(line > 0) {
        uchar *ptr=buf;
        ptr += rtu_recv_head(ptr, pkt);
        ptr += rtu_recv_data(ptr, line, &(pkt->data));

        ret = rtu_recv_crc(buf, len, pkt);
    }
    return ret;
}


bool SI_RtuRecv::recvPacket(uchar *buf, int len, SI_Rtu_Recv *pkt)
{
    bool ret = false;
    if((len > 2) && (len < 1024))
        ret = rtu_recv_packet(buf, len, pkt);
    else
        qDebug() << "SI_RtuRecv recvPacket err" << ret;

    return ret;
}
