/*
 * RTU发送数据
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "si_rtu_sent.h"


/**
  * 功　能：发送数据打包
  * 入口参数：pkt -> 发送结构体
  * 出口参数：ptr -> 缓冲区
  * 返回值：打包后的长度
  */
int SI_RtuSent::sentDataBuff(uchar addr, uchar line, uchar *buf)
{
    static SI_Rtu_Sent msg;
    static QMutex mutex; // 互拆锁
    QMutexLocker locker(&mutex);

    msg.addr = addr;
//    if(line == 1)
//        msg.len = SI_RTU_ONE_LEN;
//    else
    msg.len = SI_RTU_THREE_LEN;
    return rtu_sent_packet(&msg, buf);
}

/**
  * 功　能：发送命令数据打包
  * 入口参数：pkt -> 发送结构体
  * 出口参数：ptr -> 缓冲区
  * 返回值：打包后的长度
  */
int SI_RtuSent::sentCmdBuff(uchar addr, ushort reg, ushort value, uchar *buf)
{
    static SI_Rtu_Sent msg;
    static QMutex mutex; // 互拆锁
    QMutexLocker locker(&mutex);

    msg.addr = addr;
    msg.fn = 0x10;
    msg.reg = reg;
    msg.len = value;

    return rtu_sent_packet(&msg, buf);
}
