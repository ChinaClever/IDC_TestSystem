/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "r_rtusent.h"

R_RtuSent::R_RtuSent()
{    
    mMutex = new QMutex();
    mMsg = new R_Rtu_Sent();
}


/**
 * 功　能：发送数据打包
 * 入口参数：pkt -> 发送结构体
 * 出口参数：ptr -> 缓冲区
 * 返回值：打包后的长度
 */
int R_RtuSent::sentDataBuff(uchar addr, ushort reg, ushort len, uchar *buf)
{
   QMutexLocker locker(mMutex);

   mMsg->addr = addr;
   mMsg->fn   = 0x03;
   mMsg->reg  = reg;
   mMsg->len  = len;

   return rtu_sent_packet(mMsg, buf);
}

int R_RtuSent::sentCmdBuff(uchar addr, ushort reg, ushort value, uchar *buf)
{
   QMutexLocker locker(mMutex);

   mMsg->addr = addr;
   mMsg->fn   = 0x10;
   mMsg->reg  = reg;
   mMsg->len  = value;

   return zrtu_sent_packet(mMsg, buf);
}
