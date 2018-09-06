#ifndef IN_RTUTRANS_H
#define IN_RTUTRANS_H
#include "in_rturecv.h"
#include "eload_com/in_datapackets.h"
#include "SerialPort.h"

class IN_RtuTrans
{
    IN_RtuTrans();
public:
    static IN_RtuTrans *bulid();

    void init(SerialPort *serial);
    int transmit(int addr, sDataPacket *packet, int msecs); //发送数据并回收
    int transmit(uchar *sent, int len, uchar *recv, int msecs=5) {return mSerial->transmit(sent, len, recv,msecs);}

    bool sentSetCmd(int addr, int reg, ushort value, int msecs);
    int sendData(uchar *pBuff, int nCount, int msec=100);
    bool sentSetCmd(sRtuSentCom &cmd, int msecs);
    QByteArray getSentCmd();
    QByteArray getRecvCmd();

protected:
    void getAlarm(sDataUnit &data);
    void objData(IN_sRtuLine *data, sObjData *obj);
    void devData(IN_sRtuRecv *pkt, sDevData *dev);
    void envData(IN_sRtuRecv *pkt, sDevData *dev);
    int transData(int addr, IN_sRtuRecv *pkt, int msecs);
    void msleep(unsigned int msec);

private:
    uchar *mSentBuf, *mRecvBuf;
    int mSentLen, mRecvLen;

    QMutex *mMutex;
    bool isRun;

    IN_sRtuRecv *mRtuPkt;
    IN_RtuRecv *mRtuRecv;
    IN_RtuSent *mRtuSent;
    SerialPort *mSerial;
};

#endif // IN_RTUTRANS_H
