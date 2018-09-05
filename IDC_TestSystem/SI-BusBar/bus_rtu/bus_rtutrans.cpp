/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "bus_rtutrans.h"

BUS_RtuTrans::BUS_RtuTrans(QObject *parent) : QThread(parent)
{
    mSerial = NULL;
    isRun = false;
    mSentBuf = (uchar *)malloc(2*BUS_ARRAY_LEN);
    mRecvBuf = (uchar *)malloc(2*BUS_ARRAY_LEN);
    mMutex = new QMutex();

    mRtuPkt = new BUS_RtuRecv();
    mRtuSent = new BUS_RtuSent();
}
BUS_RtuTrans::~BUS_RtuTrans()
{
    isRun = false;
    wait();
}

BUS_RtuTrans *BUS_RtuTrans::bulid(QObject *parent)
{
    static BUS_RtuTrans* sington = NULL;
    if(sington == NULL) {
        sington = new BUS_RtuTrans(parent);
    }
    return sington;
}
/**
 * @brief 设置串口并开启线程
 * @param serial
 */
void BUS_RtuTrans::init(SerialPort *serial)
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
bool BUS_RtuTrans::sentSetCmd(int addr, int reg, ushort value, int msecs)
{
    bool ret = false;
    static uchar buf[BUS_ARRAY_LEN] = {0};
    QMutexLocker locker(mMutex);
    uchar *sent = mSentBuf;

    int len = mRtuSent->sentCmdBuff(addr, reg, value, buf);
    if(mSerial) {
        int rtn = mSerial->transmit(buf, len, sent, msecs);
        if(len == rtn) {
            if(memcmp(buf, sent,rtn) == 0)
                ret = true;
            else
                qDebug() << "bus si sent Set Cmd Err";
        }
    }

    return ret;
}


/**
 * @brief Modbus数据读取
 * @param addr 设备地址
 * @param line
 */
int BUS_RtuTrans::transData(int addr, BUS_RtuRecv *pkt, int msecs)
{
    char offLine = 0;
    uchar *sent = mSentBuf, *recv = mRecvBuf;

    int rtn = mSentLen = mRtuSent->sentDataBuff(addr, sent); // 把数据打包成通讯格式的数据
    if(mSerial) {
        rtn = mRecvLen = mSerial->transmit(sent, rtn, recv, msecs); // 传输数据，发送同时接收
    } else rtn = 0;

    if(rtn > 0)
    {
        bool ret = bus_rtu_recv_packet(recv, rtn, pkt); // 解释数据
        if(ret) {
            if(addr == pkt->addr) {
                offLine = 1;
            }
        }
    }

    return offLine;
}

void BUS_RtuTrans::loopObjData(BUS_sObjUnit *loop, BUS_RtuRecvLine *data)
{
    loop->vol.value = data->vol;
    loop->vol.min = data->minVol;
    loop->vol.max = data->maxVol;

    loop->cur.value = data->cur;
    loop->cur.min = data->minCur;
    loop->cur.max = data->maxCur;

    loop->pow = data->pow;
    loop->ele = data->ele;
    loop->pf = data->pf;
    loop->sw = data->sw;
    loop->apPow = data->apPow;
    loop->wave = data->wave;
}

void BUS_RtuTrans::loopData(sBoxData *box, BUS_RtuRecv *pkt)
{
    box->loopNum = pkt->lineNum;

    for(int i=0; i<box->loopNum; i++)
    {
        BUS_RtuRecvLine *data = &(pkt->data[i]);
        BUS_sObjUnit *loop = &(box->loop[i]);
        loop->id = i;
        loopObjData(loop, data);
    }
}

void BUS_RtuTrans::envData(sBoxData *box, BUS_RtuRecv *pkt)
{
    for(int i=0; i<BUS_SENSOR_NUM; ++i) {
        BUS_sEnvData *env = &(box->env[i]);
        env->tem.value = pkt->env[i].tem.value;
        env->tem.min = pkt->env[i].tem.min;
        env->tem.max = pkt->env[i].tem.max;
    }
}

int BUS_RtuTrans::transmit(int addr, sBoxData *box, int msecs)
{
    BUS_RtuRecv *pkt = mRtuPkt; //数据包

    int ret = transData(addr, pkt, msecs);
    if(ret) {
        loopData(box, pkt); //更新数据
        envData(box, pkt);
        box->rate = pkt->rate;
        box->dc = pkt->dc;
        box->version = pkt->version;
    }
    box->offLine = ret; //在线

    return box->offLine;
}


QByteArray BUS_RtuTrans::getSentCmd()
{
    QByteArray array;
    if((mSentLen < 0) || (mSentLen > BUS_ARRAY_LEN))  mSentLen = BUS_ARRAY_LEN;
    array.append((char *)mSentBuf, mSentLen);
    return array;
}

QByteArray BUS_RtuTrans::getRecvCmd()
{
    QByteArray array;
    if((mRecvLen < 0) || (mRecvLen > BUS_ARRAY_LEN))  mRecvLen = BUS_ARRAY_LEN;
    array.append((char *)mRecvBuf, mRecvLen);
    return array;
}
