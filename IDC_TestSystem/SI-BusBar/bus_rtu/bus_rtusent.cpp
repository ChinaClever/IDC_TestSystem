/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "bus_rtusent.h"

static ushort rtu_crc(uchar *buf, int len)
{
    return si_rtu_crc(buf, len);
}

/**
  * 功　能：发送数据打包
  * 入口参数：pkt -> 发送结构体
  * 出口参数：ptr -> 缓冲区
  * 返回值：打包后的长度
  */
static int rtu_sent_packet(BUS_Rtu_Sent *pkt, uchar *ptr)
{
    uchar *buf = ptr;
    *(ptr++) = pkt->addr;  /*地址码*/
    *(ptr++) = pkt->fn; /*功能码*/

    /*填入寄存器首地址*/
    *(ptr++) = ((pkt->reg) >> 8); /*高8位*/
    *(ptr++) = (0xff)&(pkt->reg); /*低8位*/

    /*填入数据长度*/
    *(ptr++) = ((pkt->len) >> 8); /*长度高8位*/
    *(ptr++) = (0xff)&(pkt->len); /*低8位*/

     /*填入CRC*/
    pkt->crc = rtu_crc(buf, 6);
    *(ptr++) = (0xff)&(pkt->crc); /*低8位*/
    *(ptr++) = ((pkt->crc) >> 8); /*高8位*/

    return 8;
}

/**
  * 功　能：发送数据打包
  * 入口参数：pkt -> 发送结构体
  * 出口参数：ptr -> 缓冲区
  * 返回值：打包后的长度
  */
static int rtu_sent_buff(uchar addr, uchar *buf)
{
    static BUS_Rtu_Sent msg;
    static QMutex mutex; // 互拆锁
    QMutexLocker locker(&mutex);

    msg.addr = addr;
    return rtu_sent_packet(&msg, buf);
}



static int rtu_sent_setCmd(uchar addr, ushort reg, ushort len, uchar *buf)
{
    static BUS_Rtu_Sent msg;
    static QMutex mutex; // 互拆锁
    QMutexLocker locker(&mutex);

    msg.addr = addr;
    msg.fn   = 0x10;
    msg.reg  = reg;
    msg.len  = len;
    return rtu_sent_packet(&msg, buf);
}



int BUS_RtuSent::sentDataBuff(uchar addr,  uchar *buf)
{
    return rtu_sent_buff(addr, buf);
}

int BUS_RtuSent::sentCmdBuff(uchar addr, ushort reg, ushort value, uchar *buf)
{
    return rtu_sent_setCmd(addr, reg, value, buf);
}
