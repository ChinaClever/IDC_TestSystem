/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ip_rtusent.h"

IP_RtuSent::IP_RtuSent()
{

}


/**
  * 功　能：发送数据打包
  * 入口参数：pkt -> 发送结构体
  * 出口参数：ptr -> 缓冲区
  * 返回值：打包后的长度
  */
int IP_RtuSent::sentDataBuff(uchar addr, uchar line, uchar *buf)
{
    static IP_Rtu_Sent msg;
    static QMutex mutex; // 互拆锁
    QMutexLocker locker(&mutex);

    msg.addr = addr;
    if(line == 1)
        msg.len = IP_RTU_ONE_LEN;
    else
        msg.len = IP_RTU_THREE_LEN;
    return rtu_sent_packet(&msg, buf);
}

/**
  * 功　能：发送命令数据打包
  * 入口参数：pkt -> 发送结构体
  * 出口参数：ptr -> 缓冲区
  * 返回值：打包后的长度
  */
int IP_RtuSent::sentCmdBuff(uchar addr, ushort reg, ushort value, uchar *buf)
{
    static IP_Rtu_Sent msg;
    static QMutex mutex; // 互拆锁
    QMutexLocker locker(&mutex);

    msg.addr = addr;
    msg.fn = 0x06;
    msg.reg = reg;
    msg.len = value;

    return rtu_sent_packet(&msg, buf);
}
