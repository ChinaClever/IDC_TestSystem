/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "in_rtutrans.h"
#include <QMutexLocker>
extern void setRes(int addr,int bit,int value,bool ret);
IN_RtuTrans::IN_RtuTrans()
{
    isRun = false;
    mSerial = nullptr;
    mCount = 0;

    mSentBuf = (uchar *)malloc(2*IN_ARRAY_LEN);
    mRecvBuf = (uchar *)malloc(2*IN_ARRAY_LEN);
    mMutex = new QMutex();

    mRtuPkt = new IN_sRtuRecv();
    mRtuRecv = new IN_RtuRecv();
    mRtuSent = new IN_RtuSent();
}

IN_RtuTrans *IN_RtuTrans::bulid()
{
    static IN_RtuTrans* sington = nullptr;
    if(sington == nullptr)
        sington = new IN_RtuTrans();
    return sington;
}

void IN_RtuTrans::init(SerialPort *serial)
{
    mSerial = serial;
}

void IN_RtuTrans::msleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

int IN_RtuTrans::sendData(uchar *pBuff, int nCount, int msec)
{
    QMutexLocker locker(mMutex); msleep(msec);
    int ret = mSerial->write(pBuff, nCount);
    if(ret>=0) msleep(msec);

    return ret;
}

int IN_RtuTrans::transCmd(uchar *pBuff, int nCount, int msec)
{
    QMutexLocker locker(mMutex); msleep(300);
    uchar *sent = mSentBuf;//recv
    int rtn = 0;
    if(mSerial) {
    rtn = mSerial->transmit(pBuff, nCount, sent, msec);
    }
    //msleep(300);
    return rtn;
}

/**
 * @brief 发送设置命令
 * @param addr 地址
 * @param reg 寄存吕
 * @param value 值
 * @return true
 */
bool IN_RtuTrans::sentSetCmd(int addr,int fn, int reg, ushort value, int msecs)
{
    bool ret = false;
    static uchar buf[IN_ARRAY_LEN] = {0};
    QMutexLocker locker(mMutex); msleep(300);
    uchar *sent = mSentBuf;
    int len = mRtuSent->sentCmdBuff(addr,fn, reg, value, buf);//打包数据
    if(mSerial) {
        int rtn = mSerial->transmit(buf, len, sent, msecs);
        if(len == rtn) {
            if(memcmp(buf, sent,rtn) == 0){
                ret = true;
                if(sent[1] == 0x11){
                setRes(sent[0],sent[3],(sent[4]*256+sent[5]),ret);
                memset(mSentBuf,0,len);
                return ret;
                }
            }
            else{
                qDebug() << "IN si sent Set Cmd Err";
            }
        }
        if(!ret) setRes(-1,0,1,ret);
    }
    msleep(300);

    return ret;
}

bool IN_RtuTrans::sentSetCmd(sRtuSentCom &cmd, int msecs)
{
    return sentSetCmd(cmd.addr,cmd.fn ,cmd.reg, cmd.len, msecs);
}

/**
 * @brief Modbus数据读取
 * @param addr 设备地址
 * @param line
 */
int IN_RtuTrans::transData(int addr, IN_sRtuRecv *pkt, int msecs)
{
    char offLine = 0;
    QMutexLocker locker(mMutex);
    uchar *sent = mSentBuf, *recv = mRecvBuf;

    int rtn = mSentLen = mRtuSent->sentDataBuff(addr, sent); // 把数据打包成通讯格式的数据
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
    return offLine;
}


void IN_RtuTrans::getAlarm(sDataUnit &data)
{
    if((data.value < data.min) || (data.value > data.max)) {
        if(data.alarm == 0)
            data.alarm = 1;
    } else {
        data.alarm = 0;
    }
}


void IN_RtuTrans::objData(IN_sRtuLine *data, sObjData *obj)
{
    obj->vol.value = data->vol;
    obj->vol.min = data->minVol;
    obj->vol.max = data->maxVol;
    getAlarm(obj->vol);

    obj->cur.value = data->cur;
    obj->cur.min = data->minCur;
    obj->cur.max = data->maxCur;
    getAlarm(obj->cur);

    obj->pow = data->pow;
    obj->ele = data->ele;
    obj->pf = data->pf;

    obj->activePow = data->apPow;
    obj->wave = data->wave;
    //obj->sw = data->sw;
}


void IN_RtuTrans::devData(IN_sRtuRecv *pkt, sDevData *dev)
{
    dev->inputNum = pkt->lineNum;


    for(int i=0; i<dev->inputNum; i++)
    {
        IN_sRtuLine *data = &(pkt->data[i]);
        sObjData *obj = &(dev->input[i]);
        obj->id = i;
        objData(data, obj);
    }
}

void IN_RtuTrans::envData(IN_sRtuRecv *pkt, sDevData *dev)
{
    for(int i=0; i<SENOR_NUM; ++i) {
        sDataUnit *env = &(dev->env.tem[i]);
        env->value = pkt->env[i].tem.value;
        env->min = pkt->env[i].tem.min;
        env->max = pkt->env[i].tem.max;
        getAlarm(*env);
    }
}

int IN_RtuTrans::transmit(int addr, sDataPacket *packet, int msecs)
{
    IN_sRtuRecv *pkt = mRtuPkt; //数据包

    int ret = transData(addr, pkt, msecs);
    if(ret) {
        devData(pkt, &(packet->data)); //更新数据
        envData(pkt, &(packet->data));
        packet->id = addr;
        packet->hz = pkt->rate;
        packet->dc = pkt->dc;
        packet->version = pkt->version;
    }
    packet->offLine = ret; //在线

    return packet->offLine;
}

void IN_RtuTrans::transgetStatus(int addr, sDataPacket *packet, int msecs)
{
    QMutexLocker locker(mMutex);
    static uchar sent[8] , recv[8];

    int rtn = mSentLen = mRtuSent->sentGetStatusBuff(addr, sent);
    if(mSerial) {
        rtn = mRecvLen = mSerial->transmit(sent, rtn, recv, msecs); // 传输数据，发送同时接收
    } else rtn = 0;

    sDevData* dev = &(packet->data);
    if(rtn && addr == recv[0] && recv[1] == 0x07) {
        for(int i=0; i<dev->inputNum; i++)
        {
            sObjData *obj = &dev->input[i];
            obj->sw = (recv[5]>>(8-i-1))&0x01;
        }
        mCount = 0;
    }
    else{
        if(mCount == 0){
            for(int i=0; i<dev->inputNum; i++)
            {
                sObjData *obj = &dev->input[i];
                obj->sw = 0x01;
            }
            mCount ++;
        }
        else{//第二次没有接收到返回才判断失败
            for(int i=0; i<dev->inputNum; i++)
            {
                sObjData *obj = &dev->input[i];
                obj->sw = 0x00;
            }
        }
    }
}

QByteArray IN_RtuTrans::getSentCmd()
{
    QByteArray array;
    if((mSentLen < 0) || (mSentLen > IN_ARRAY_LEN))  mSentLen = IN_ARRAY_LEN;
    array.append((char *)mSentBuf, mSentLen);
    return array;
}

QByteArray IN_RtuTrans::getRecvCmd()
{
    QByteArray array;
    if((mRecvLen < 0) || (mRecvLen > IN_ARRAY_LEN))  mRecvLen = IN_ARRAY_LEN;
    array.append((char *)mRecvBuf, mRecvLen);
    return array;
}
