/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "eload_rtusent.h"
#include "eload_rtu/in_rtuthread.h"
ELoad_RtuSent::ELoad_RtuSent()
{
    mSerial = IN_RtuTrans::bulid();
    mSentBuf = (uchar *)malloc(256);
    mAddr = -1;
    mBit = -1;
    for(int i = 0 ; i < 3 ; i ++)
        for(int j = 0 ;j < 8 ; j ++)
            mFlag.append(false);
}


ELoad_RtuSent *ELoad_RtuSent::bulid()
{
    static ELoad_RtuSent* sington = nullptr;
    if(sington == nullptr) {
        sington = new ELoad_RtuSent();
    }
    return sington;
}

int ELoad_RtuSent::setDataBuf(uchar addr, uchar fn, ushort reg, ushort value)
{
    uchar *buf = mSentBuf;
    sRtuSentCom cmd;
    cmd.addr = addr;
    cmd.fn = fn;
    cmd.reg = reg;
    cmd.len = value;
    int rtn = rtu_sent_packet(&cmd, buf);
    IN_RtuThread::bulid()->sentCmd(cmd);
    //return mSerial->sendData(buf, rtn);
    //return mSerial->transCmd(buf,rtn,10);
    return rtn;
}

/**
 * @brief 设置数据参数
 * @param addr  从机地址  从机地址可设置范围：1~15
 * @param reg 数字电位器地址  1 ~ 8
 * @param value   参数（数字电位器阻值）可设置范围：40Ω~50KΩ
 * @param buf 数据缓冲区
 * @return 数据长度
 */
int ELoad_RtuSent::setData(uchar addr, ushort reg, ushort value)
{
    return setDataBuf(addr, ELoad_FN_Set, reg, value);
}

/**
 * @brief 设置数据参数
 * @param addr  从机地址  从机地址可设置范围：1~15
 * @param reg 数字电位器地址  1 ~ 8
 * @param value   参数（数字电位器阻值）可设置范围：40Ω~50KΩ
 * @param buf 数据缓冲区
 * @return 数据长度
 */
int ELoad_RtuSent::setResData(uchar addr, ushort reg, ushort value)
{
    mAddr = addr;
    mBit = reg - ELoad_DP_1;
    mFlag[(mAddr-1)*8+mBit] = true;
    return setDataBuf(addr, ELoad_FN_Set, reg, value);
}

/**
 * @brief 提供给ELoad_InputUnitWid类界面自动更新阻值
 * @param [in&out]addr  从机地址  从机地址可设置范围：1~15
 *        [in&out]reg 数字电位器地址  1 ~ 8
 *        [in&out]flag  自动改变阻值标志位
 */
void ELoad_RtuSent::getValue(int& addr , int& bit, QList<bool>& flag)
{
    addr = mAddr;
    bit = mBit;
    flag = mFlag;
}

/**
 * @brief 提供给ELoad_InputUnitWid类界面自动更新阻值
 * @param [in&out]flag  自动改变阻值标志位
 */
void ELoad_RtuSent::setValue(int& addr , int& bit ,QList<bool>& flag)
{
    mAddr = addr;
    mBit = bit;
    mFlag = flag;
}

/**
 * @brief 波特率设置
 * @param addr
 * @param reg
 * @param value
 * @param buf
 * @return
 */
int ELoad_RtuSent::setBaudRate(uchar addr, ushort reg, ushort value)
{
    return setDataBuf(addr, ELoad_BR_Reg, reg, value);
}

int ELoad_RtuSent::switchOpenCtr(uchar addr,  uchar bit)
{
    uchar cmd[16] = {0x7B, 0xA1, 0x10, 0x00, 0x00, 0x00, 0xC7, 0xC8, 0xC9, 0x00, 0x00, 0x00, 0xD7, 0xD8, 0xD9, 0x25};
    uchar sw = 0x80;
    sw >>= bit;
    cmd[3+addr-1] = sw;

    int offset = 15;
    ushort xorsum =rtu_xorsum(cmd, offset);
    cmd[offset++] = xorsum ;

    uchar *buf = mSentBuf;
    for(int i=0; i<offset; ++i) buf[i] = cmd[i];

    //return mSerial->sendData(buf, offset);
    return mSerial->transCmd(buf,offset,10);
}

int ELoad_RtuSent::switchOpenAll()
{
    uchar cmd[16] = {0x7B, 0xA1, 0x10, 0xFF, 0xFF, 0xFF, 0xC7, 0xC8, 0xC9, 0x00, 0x00, 0x00, 0xD7, 0xD8, 0xD9, 0x25};

    int offset = 15;
    uchar crc =rtu_xorsum(cmd, offset);

    cmd[offset++] = crc ;

    uchar *buf = mSentBuf;
    for(int i=0; i<offset; ++i) buf[i] = cmd[i];

    //return mSerial->sendData(buf, offset);
    return mSerial->transCmd(buf,offset,10);
}

int ELoad_RtuSent::switchCloseCtr(uchar addr,  uchar bit)
{
    uchar cmd[16] = {0x7B, 0xA1, 0x10, 0x00, 0x00, 0x00, 0xC7, 0xC8, 0xC9, 0x00, 0x00, 0x00, 0xD7, 0xD8, 0xD9, 0x25};
    uchar sw = 0x80;
    sw >>= bit;
    cmd[9+addr-1] = sw;

    int offset = 15;
    uchar crc =rtu_xorsum(cmd, offset);
    cmd[offset++] = crc;

    uchar *buf = mSentBuf;
    for(int i=0; i<offset; ++i) buf[i] = cmd[i];

    //return mSerial->sendData(buf, offset);
    return mSerial->transCmd(buf,offset,10);
}

int ELoad_RtuSent::switchCloseAll()
{
    uchar cmd[16] = {0x7B, 0xA1, 0x10, 0x00, 0x00, 0x00, 0xC7, 0xC8, 0xC9, 0xFF, 0xFF, 0xFF, 0xD7, 0xD8, 0xD9, 0x25};

    int offset = 15;
    uchar crc =rtu_xorsum(cmd, offset);
    cmd[offset++] = crc ;

    uchar *buf = mSentBuf;
    for(int i=0; i<offset; ++i) buf[i] = cmd[i];

    //return mSerial->sendData(buf, offset);
    return mSerial->transCmd(buf,offset,10);
}

int ELoad_RtuSent::setDpAdjust(uchar addr, ushort reg, ushort start, ushort end, ushort t)
{
    int offset = 0;
    uchar *buf = mSentBuf;

    buf[offset++] = addr;
    buf[offset++] = ELoad_FN_Ctr;

    buf[offset++] = (reg >> 8);
    buf[offset++] = (reg & 0xff);

    buf[offset++] =  (start >> 8);
    buf[offset++] = (start & 0xff);

    buf[offset++] =  (end >> 8);
    buf[offset++] = (end & 0xff);

    buf[offset++] =  (t >> 8);
    buf[offset++] = (t & 0xff);

    ushort crc =rtu_crc(buf, offset);
    buf[offset++] = (crc >> 8);
    buf[offset++] = (crc & 0xff);

    //return mSerial->sendData(buf, offset);
    return mSerial->transCmd(buf,offset,10);
}

int ELoad_RtuSent::setAllDpAdjust(uchar addr, ushort start, ushort end, ushort t)
{
    int offset = 0;
    uchar *buf = mSentBuf;

    buf[offset++] = addr;
    buf[offset++] = ELoad_FN_AllCtr;

    buf[offset++] =  (start >> 8);
    buf[offset++] = (start & 0xff);

    buf[offset++] =  (end >> 8);
    buf[offset++] = (end & 0xff);

    buf[offset++] =  (t >> 8);
    buf[offset++] = (t & 0xff);

    ushort crc =rtu_crc(buf, offset);
    buf[offset++] = (crc >> 8);
    buf[offset++] = (crc & 0xff);

    //return mSerial->sendData(buf, offset);
    return mSerial->transCmd(buf,offset,10);
}

void Delay_MSec(unsigned int msec)
{
    QTime _Timer = QTime::currentTime().addMSecs(msec);

    while( QTime::currentTime() < _Timer )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

int ELoad_RtuSent::setAllDpAdjust()
{
    for(int i=0; i<3; ++i)
    {
        setAllDpAdjust(i+1, 1000, 10000, 60000);
        Delay_MSec(1000);
    }
}

/**
 * @brief
 * @param [in]addr[1-3]：对应地址的电子负载,sw[0，1]：0为关闭大电流模式，1为打开大电流模式
 * @return int 接收到的字节数
 */
int ELoad_RtuSent::setBigCur(uchar addr, uchar sw)
{
    uchar cmd[16] = {0x7B, 0xA6, 0x01, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCD};
    cmd[2] = addr;
    cmd[4] = sw;

    int offset = 15;
    uchar crc =rtu_xorsum(cmd, offset);
    cmd[offset++] = crc;

    uchar *buf = mSentBuf;
    for(int i=0; i<offset; ++i) buf[i] = cmd[i];

    //return mSerial->sendData(buf, offset);
    return mSerial->transCmd(buf,offset,10);
}

int ELoad_RtuSent::getHandshake(uchar addr)
{
    uchar cmd[10] = {0x7B, 0xB1, 0x01, 0x08, 0x11, 0x22};
    cmd[2] = addr;

    int offset = 6;
    ushort crc =rtu_crc(cmd, offset);
    cmd[offset++] = (crc >> 8);
    cmd[offset++] = (crc & 0xff);

    return mSerial->transmit(cmd,offset, mSentBuf);
}
