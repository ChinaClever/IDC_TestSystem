/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "r_rtutrans.h"

R_RtuTrans::R_RtuTrans()
{
    mSerial = NULL;
    isRun = false;
    mSentBuf = (uchar *)malloc(2*SERIAL_LEN);
    mRecvBuf = (uchar *)malloc(2*SERIAL_LEN);
    mMutex = new QMutex();

    mRtuPkt = new  ZM_sRtuRecv();
    mRtuSent = new R_RtuSent();
    mRtuRecv = new R_RtuRecv();
}


R_RtuTrans *R_RtuTrans::bulid()
{
    static R_RtuTrans* sington = NULL;
    if(sington == NULL) {
        sington = new R_RtuTrans();
    }
    return sington;
}


/**
 * @brief 设置串口并开启线程
 * @param serial
 */
void R_RtuTrans::init(SerialPort *serial)
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
bool R_RtuTrans::sentSetCmd(int addr, int reg, ushort value, int msecs)
{
    bool ret = true;//暂时，因为有时又回复，有时没有回复
    static uchar buf[SERIAL_LEN] = {0};
    QMutexLocker locker(mMutex);
    uchar *sent = mSentBuf;

    int len = mRtuSent->sentCmdBuff(addr, reg, value, buf);
    QByteArray writeArray, readArray;
    writeArray.append((char *)buf, len);

    //cm_PrintHex("write:" , writeArray);
    if(mSerial) {
        int rtn = mSerial->transmit(buf, len, sent, msecs+5);

        readArray.append((char *)sent, rtn);
        //cm_PrintHex("read:" , readArray);
//        if(rtn != 8)
//         {
//            memset(sent,0,rtn);
//            memset(mSentBuf,0,rtn);
//            sleep(5);
//            rtn = mSerial->transmit(buf, len, sent, msecs+5);//修改两次 2019/7/30

//            strArray.clear();
//            readArray.append((char *)sent, rtn);
//            strArray = readArray.toHex(); // 十六进制
//            for(int i=0; i<readArray.size(); ++i)
//            strArray.insert(2+3*i, " "); // 插入空格
//            qDebug()<< "read2:" << strArray<<mSerial;
//        }
        if(memcmp(sent, buf,rtn) == 6)
            ret = true;
    }

    return ret;
}


/**
 * @brief Modbus数据读取
 * @param addr 设备地址
 * @param line
 */
int R_RtuTrans::transData(int addr, ushort reg, ushort len, ZM_sRtuRecv *pkt, int msecs)
{
    uchar offLine = 0;
    uchar *sent = mSentBuf, *recv = mRecvBuf;

    int rtn = mSentLen = mRtuSent->sentDataBuff(addr, reg, len, sent); // 把数据打包成通讯格式的数据
    if(mSerial) {
        rtn = mRecvLen = mSerial->transmit(sent, rtn, recv, msecs); // 传输数据，发送同时接收
    } else rtn = 0;

    if(rtn > 0)
    {
        bool ret = mRtuRecv->recvPacket(recv, rtn, reg, pkt); // 解释数据
        if(ret) {
            if(addr == pkt->addr) {
                offLine = 1;
            }
        }
    }
    pkt->offLine = offLine;

    return offLine;
}


int R_RtuTrans::transData(int addr, int cmd, sDataPacket *pkt, int msecs)
{
    ushort *array = r_reg_array(cmd);
    int ret = transData(addr, array[0], array[1], mRtuPkt, msecs);
    if(ret)  {devDataPacket(mRtuPkt, pkt);}
    else pkt->id = addr;

    return ret;
}


QByteArray R_RtuTrans::getSentCmd()
{
    QByteArray array;
    if((mSentLen < 0) || (mSentLen > SERIAL_LEN))  mSentLen = SERIAL_LEN;
    array.append((char *)mSentBuf, mSentLen);
    return array;
}

QByteArray R_RtuTrans::getRecvCmd()
{
    QByteArray array;
    if((mRecvLen < 0) || (mRecvLen > SERIAL_LEN))  mRecvLen = SERIAL_LEN;
    array.append((char *)mRecvBuf, mRecvLen);
    return array;
}

void R_RtuTrans::getAlarm(sDataUnit &data)
{
    if((data.value < data.min) || (data.value > data.max)) {
        if(data.alarm == 0)
            data.alarm = 1;
    } else {
        data.alarm = 0;
    }
}

void R_RtuTrans::dataUnit(int i, ZM_sDataUnit &rtu, sDataUnit &data, int rate)
{
    data.value = rtu.value[i] / rate;
    data.min = data.crMin = rtu.min[i] / rate;
    data.max = data.crMax = rtu.max[i] / rate;

    getAlarm(data);
}

void R_RtuTrans::devObjData(ZM_sObjData &rtuData, int i, sObjData &data , bool flag)
{
    data.id = i;
    dataUnit(i, rtuData.vol, data.vol, 1);
    dataUnit(i, rtuData.cur, data.cur, 1);
    data.ele = rtuData.ele[i];
    data.activePow = data.vol.value * data.cur.value / 1;
    data.pf = rtuData.pf[i];
    data.sw = rtuData.sw[i];

    if(flag)
    {
        if(data.sw != 1)
        {
            if(data.vol.value)
            {
                data.sw = 1;
            }
            else  data.sw = 0;
        }
    }
    if(rtuData.pow[i] > 0) {
        data.pow = rtuData.pow[i] / 1000;
    } else {
        data.pow = data.activePow * data.pf / 100.0;
    }
}

void R_RtuTrans::envData(ZM_sEnv &rtuData, sEnvData &data)
{
    data.envNum = 4;

    for(int i=0; i<data.envNum; ++i) {
        dataUnit(i, rtuData.tem, data.tem[i]);
        dataUnit(i, rtuData.hum, data.hum[i]);

        data.door[i] = rtuData.door[i];
        data.water[i] = rtuData.water[i];
        data.smoke[i] = rtuData.smoke[i];
    }
}

void R_RtuTrans::devData(ZM_sRtuPacket &rtuData, sDevData &data)
{
    int vol = 220;

    int num = data.lineNum = rtuData.line.num;
    for(int i=0; i<num; ++i) {
        devObjData(rtuData.line, i, data.line[i] , true);
        vol = rtuData.line.vol.value[0];
    }

    num = data.loopNum = rtuData.loop.num;
    for(int i=0; i<num; ++i) {
        devObjData(rtuData.loop, i, data.loop[i] , data.line[i/2].sw);
         data.loop[i].vol.alarm = data.loop[i].vol.crAlarm = 0;
    }

    if(data.outputNum == 0)
    num = data.outputNum = rtuData.output.num;
    else
    num = rtuData.output.num = data.outputNum;
    for(int i=0; i<num; ++i) {
        rtuData.output.vol.value[i] = vol;
        devObjData(rtuData.output, i, data.output[i] ,false);
        data.output[i].vol.alarm = data.output[i].vol.crAlarm = 0;
    }

    envData(rtuData.env, data.env);
}

void R_RtuTrans::devDataPacket(ZM_sRtuRecv *pkt, sDataPacket *packet)
{
    packet->id = pkt->addr;
    packet->offLine = pkt->offLine;
    packet->devSpec = pkt->data.devSpec;
    //strcpy(packet->ip, pkt->data.ip);
    packet->txType = 2;

    devData(pkt->data, packet->data);
}
