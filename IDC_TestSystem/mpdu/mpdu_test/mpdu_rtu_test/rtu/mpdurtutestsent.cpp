#include "mpdurtutestsent.h"



MpduRtuTestSent::MpduRtuTestSent()
{

}

/**
  * 功　能：发送数据打包
  * 入口参数：pkt -> 发送结构体
  * 出口参数：ptr -> 缓冲区
  * 返回值：打包后的长度
  */
int MpduRtuTestSent::sentDataBuff(uchar addr, uchar len, uchar *buf)
{
    static MPDU_RtuTest_Sent msg;
    static QMutex mutex; // 互拆锁
    QMutexLocker locker(&mutex);

    msg.addr = addr;
    msg.len = len;

    return rtu_sent_packet(&msg, buf);
}

/**
  * 功　能：发送命令数据打包
  * 入口参数：pkt -> 发送结构体
  * 出口参数：ptr -> 缓冲区
  * 返回值：打包后的长度
  */
int MpduRtuTestSent::sentCmdBuff(uchar addr, ushort reg, ushort value, uchar *buf)
{
    static MPDU_RtuTest_Sent msg;
    static QMutex mutex; // 互拆锁
    QMutexLocker locker(&mutex);

    msg.addr = addr;
    msg.fn = 0x06;
    msg.reg = reg;
    msg.len = value;

    return rtu_sent_packet(&msg, buf);
}
