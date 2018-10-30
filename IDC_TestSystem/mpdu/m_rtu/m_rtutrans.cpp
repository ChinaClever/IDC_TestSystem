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
    QMutexLocker locker(mMutex);
    uchar *sent = mSentBuf;

    int len = mRtuSent->sentCmdBuff(addr, reg, value, buf);
    if(mSerial) {
        int rtn = mSerial->transmit(buf, len, sent, msecs);
        if(len == rtn) {
            if(memcmp(buf, sent,rtn) == 0)
                ret = true;
            else
                qDebug() << "M sent Set Cmd Err";
        }
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
    } else rtn = 0;

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
    static ushort array[ZM_RtuReg_CmdNum][2] = {
        ZM_RtuReg_DevType,       ZM_RtuReg_DevTypeSize,
        ZM_RtuReg_DevIP,         ZM_RtuReg_DevIPSize,
        ZM_RtuReg_DevMac,        ZM_RtuReg_DevMacSize,
        ZM_RtuReg_OutputNum,     ZM_RtuReg_OutputNumSize,
        ZM_RtuReg_OutputSw,      ZM_RtuReg_OutputSwSize,

        ZM_RtuReg_LineCur,        ZM_RtuReg_LineCurSize,
        ZM_RtuReg_LineCurMin,     ZM_RtuReg_LineCurMinSize,
        ZM_RtuReg_LineCurMax,     ZM_RtuReg_LineCurMaxSize,
        ZM_RtuReg_LineCurCrMin,   ZM_RtuReg_LineCurCrMinSize,
        ZM_RtuReg_LineCurCrMax,   ZM_RtuReg_LineCurCrMaxSize,

        ZM_RtuReg_LineVol,        ZM_RtuReg_LineVolSize,
        ZM_RtuReg_LineVolMin,        ZM_RtuReg_LineVolMinSize,
        ZM_RtuReg_LineVolMax,        ZM_RtuReg_LineVolMaxSize,
        ZM_RtuReg_LineVolCrMin,        ZM_RtuReg_LineVolCrMinSize,
        ZM_RtuReg_LineVolCrMax,        ZM_RtuReg_LineVolCrMaxSize,

        ZM_RtuReg_LinePow ,        ZM_RtuReg_LinePowSize,
        ZM_RtuReg_LinePF ,        ZM_RtuReg_LinePFSize,
        ZM_RtuReg_LineEle ,        ZM_RtuReg_LineEleSize,

        ZM_RtuReg_LoopCur ,        ZM_RtuReg_LoopCurSize ,
        ZM_RtuReg_LoopCurMin ,        ZM_RtuReg_LoopCurMinSize ,
        ZM_RtuReg_LoopCurMax ,        ZM_RtuReg_LoopCurMaxSize ,
        ZM_RtuReg_LoopCurCrMin ,        ZM_RtuReg_LoopCurCrMinSize ,
        ZM_RtuReg_LoopCurCrMax ,        ZM_RtuReg_LoopCurCrMaxSize ,

        ZM_RtuReg_LoopVol ,        ZM_RtuReg_LoopVolSize ,
        ZM_RtuReg_LoopEle ,        ZM_RtuReg_LoopEleSize ,

        ZM_RtuReg_OutputCur ,        ZM_RtuReg_OutputCurSize ,
        ZM_RtuReg_OutputCurMin ,        ZM_RtuReg_OutputCurMinSize ,
        ZM_RtuReg_OutputCurMax ,        ZM_RtuReg_OutputCurMaxSize ,
        ZM_RtuReg_OutputCurCrMin ,        ZM_RtuReg_OutputCurCrMinSize ,
        ZM_RtuReg_OutputCurCrMax ,        ZM_RtuReg_OutputCurCrMaxSize ,
        ZM_RtuReg_OutputPF ,        ZM_RtuReg_OutputPFSize ,
        ZM_RtuReg_OutputEle ,        ZM_RtuReg_OutputEleSize ,

        ZM_RtuReg_TemData ,        ZM_RtuReg_TemSize ,
        ZM_RtuReg_TemMin ,        ZM_RtuReg_TemMinSize ,
        ZM_RtuReg_TemMax ,        ZM_RtuReg_TemMaxSize ,
        ZM_RtuReg_TemCrMin ,        ZM_RtuReg_TemCrMinSize ,
        ZM_RtuReg_TemCrMax ,        ZM_RtuReg_TemCrMaxSize ,

        ZM_RtuReg_HumData ,        ZM_RtuReg_HumSize ,
        ZM_RtuReg_HumMin ,        ZM_RtuReg_HumMinSize ,
        ZM_RtuReg_HumMax ,        ZM_RtuReg_HumMaxSize,
        ZM_RtuReg_HumCrMin ,        ZM_RtuReg_HumCrMinSize ,
        ZM_RtuReg_HumCrMax ,        ZM_RtuReg_HumCrMaxSize ,

        ZM_RtuReg_DoorData ,        ZM_RtuReg_DoorSize ,
        ZM_RtuReg_WaterData ,        ZM_RtuReg_WaterSize ,
        ZM_RtuReg_SmokeData ,        ZM_RtuReg_SmokeSize ,
    };

    int ret = transData(addr, array[cmd][0], array[cmd][1], mRtuPkt, msecs);
    if(ret)  {devDataPacket(mRtuPkt, pkt); pkt->txType = 2;}
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

