#ifndef IP_RTUTRANS_H
#define IP_RTUTRANS_H
#include "ip_rturecv.h"

class IP_RtuTrans
{
    IP_RtuTrans();

public:
    static IP_RtuTrans *bulid();
    ~IP_RtuTrans();

    void init(SerialPort *serial);
    bool sentSetCmd(int addr, int reg, ushort value, int msecs);
    int transData(int addr, int line, IP_Rtu_Recv *pkt, int msecs);
    QByteArray getSentCmd();
    QByteArray getRecvCmd();

private:
    uchar *mSentBuf, *mRecvBuf;
    int mSentLen, mRecvLen;

    SerialPort *mSerial;
    QMutex *mMutex;
    bool isRun;

    IP_RtuSent *mRtuSent;
    IP_RtuRecv *mRtuRecv;
};

#endif // IP_RTUTRANS_H
