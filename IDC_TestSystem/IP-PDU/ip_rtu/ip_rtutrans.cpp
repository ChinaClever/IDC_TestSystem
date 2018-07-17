#include "ip_rtutrans.h"

IP_RtuTrans::IP_RtuTrans()
{
    mSerial = NULL;
    isRun = false;
    mSentBuf = (uchar *)malloc(2*SERIAL_LEN);
    mRecvBuf = (uchar *)malloc(2*SERIAL_LEN);
    mMutex = new QMutex();

    mRtuSent = new IP_RtuSent();
    mRtuRecv = new IP_RtuRecv();
}


IP_RtuTrans *IP_RtuTrans::bulid()
{
    static IP_RtuTrans* sington = NULL;
    if(sington == NULL) {
        sington = new IP_RtuTrans();
    }
    return sington;
}

/**
 * @brief 设置串口并开启线程
 * @param serial
 */
void IP_RtuTrans::init(SerialPort *serial)
{
    mSerial = serial;
}


/**
 * @brief 发送设置命令
 * @param addr 地址
 * @param reg 寄存吕
 * @param value 值
 * @return true
 */
bool IP_RtuTrans::sentSetCmd(int addr, int reg, ushort value, int msecs)
{
    bool ret = false;
    static uchar buf[SERIAL_LEN] = {0};
    QMutexLocker locker(mMutex);
    uchar *sent = mSentBuf;

    int len = mRtuSent->sentCmdBuff(addr, reg, value, buf);
    if(mSerial) {
        int rtn = mSerial->transmit(buf, len, sent, msecs);
        if(len == rtn) {
            if(memcmp(buf, sent,rtn) == 0)
                ret = true;
            else
                qDebug() << "IP sent Set Cmd Err";
        }
    }

    return ret;
}


/**
 * @brief Modbus数据读取
 * @param addr 设备地址
 * @param line
 */
int IP_RtuTrans::transData(int addr, int line, IP_Rtu_Recv *pkt, int msecs)
{
    char offLine = 0;
    uchar *sent = mSentBuf, *recv = mRecvBuf;

    int rtn = mSentLen = mRtuSent->sentDataBuff(addr, line,sent); // 把数据打包成通讯格式的数据
    if(mSerial) {
        rtn = mRecvLen = mSerial->transmit(sent, rtn, recv, msecs); // 传输数据，发送同时接收
    } else rtn = 0;

    if(rtn > 0)
    {
        bool ret = mRtuRecv->recvPacket(recv, rtn, pkt); // 解释数据
        if(ret) {
            if(addr == pkt->addr) {
                offLine = 1;
            }
        }
    }
    pkt->offLine = offLine;

    return offLine;
}

QByteArray IP_RtuTrans::getSentCmd()
{
    QByteArray array;
    if((mSentLen < 0) || (mSentLen > SERIAL_LEN))  mSentLen = SERIAL_LEN;
    array.append((char *)mSentBuf, mSentLen);
    return array;
}



QByteArray IP_RtuTrans::getRecvCmd()
{
    QByteArray array;
    if((mRecvLen < 0) || (mRecvLen > SERIAL_LEN))  mRecvLen = SERIAL_LEN;
    array.append((char *)mRecvBuf, mRecvLen);
    return array;
}
