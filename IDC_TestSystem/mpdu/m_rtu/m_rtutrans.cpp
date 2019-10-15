/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "m_rtutrans.h"

M_RtuTrans::M_RtuTrans()
{
    mSerial = NULL;
    isRun = false;
    mSentBuf = (uchar *)malloc(2*SERIAL_LEN);
    mRecvBuf = (uchar *)malloc(2*SERIAL_LEN);
    mMutex = new QMutex();

    mRtuPkt = new  ZM_sRtuRecv();
    mRtuSent = new M_RtuSent();
    mRtuRecv = new M_RtuRecv();
}

M_RtuTrans *M_RtuTrans::bulid()
{
    static M_RtuTrans* sington = NULL;
    if(sington == NULL) {
        sington = new M_RtuTrans();
    }
    return sington;
}


/**
 * @brief 设置串口并开启线程
 * @param serial
 */
void M_RtuTrans::init(SerialPort *serial)
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
bool M_RtuTrans::sentSetCmd(int addr, int reg, ushort value, int msecs)
{
    bool ret = false;
    static uchar buf[SERIAL_LEN] = {0};

    static uchar normalbuf[5] = {0x01,0x60,0x01,0xC9,0xC0};
    static uchar abnormalbuf[5] = {0x01,0x90,0x02,0xCD,0xC1};

    QMutexLocker locker(mMutex);
    uchar *sent = mSentBuf;

    int len = mRtuSent->sentCmdBuff(addr, reg, value, buf);
    if(mSerial) {
        int rtn = mSerial->transmit(buf, len, sent, msecs);
        if(5 == rtn) {
            if(memcmp(sent, normalbuf,rtn) == 0)
                ret = true;
            else if(memcmp(sent, abnormalbuf,rtn) == 0)
                qDebug() << "M sent Set Cmd Err";
        }
        if(0 == rtn)
            return true;//由于MPDU不回答，暂时是正确的
    }

    return ret;
}


/**
 * @brief Modbus数据读取
 * @param addr 设备地址
 * @param line
 */
int M_RtuTrans::transData(int addr, ushort reg, ushort len, ZM_sRtuRecv *pkt, int msecs)
{
    uchar offLine = 0;
    uchar *sent = mSentBuf, *recv = mRecvBuf;

    int rtn = mSentLen = mRtuSent->sentDataBuff(addr, reg, len, sent); // 把数据打包成通讯格式的数据
    if(mSerial) {
        rtn = mRecvLen = mSerial->transmit(sent, rtn, recv, msecs); // 传输数据，发送同时接收
    } else {
        rtn = 0;
    }

    if(rtn > 0)
    {
        bool ret = mRtuRecv->recvPacket(recv, rtn, reg,pkt); // 解释数据
        if(ret) {
            if(addr == pkt->addr) {
                offLine = 1;
            }
        }
    }
    pkt->offLine = offLine;

    return offLine;
}

int M_RtuTrans::transData(int addr, int cmd, sDataPacket *pkt, int msecs)
{
    ushort *array = zm_reg_array(cmd);
    int ret = transData(addr, array[0], array[1], mRtuPkt, msecs);
    if(ret){ devDataPacket(mRtuPkt, pkt);}
    else pkt->id = addr;

    return ret;
}

QByteArray M_RtuTrans::getSentCmd()
{
    QByteArray array;
    if((mSentLen < 0) || (mSentLen > SERIAL_LEN))  mSentLen = SERIAL_LEN;
    array.append((char *)mSentBuf, mSentLen);
    return array;
}

QByteArray M_RtuTrans::getRecvCmd()
{
    QByteArray array;
    if((mRecvLen < 0) || (mRecvLen > SERIAL_LEN))  mRecvLen = SERIAL_LEN;
    array.append((char *)mRecvBuf, mRecvLen);
    return array;
}

