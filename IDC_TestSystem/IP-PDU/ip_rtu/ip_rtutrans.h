#ifndef IP_RTUTRANS_H
#define IP_RTUTRANS_H
#include "ip_rturecv.h"
#include "rtutrans.h"

class IP_RtuTrans : public RtuTrans
{
    IP_RtuTrans();

public:
    static IP_RtuTrans *bulid();

    void init(SerialPort *serial);
    bool sentSetCmd(int addr, int reg, ushort value, int msecs);
    int transData(int addr, int line, sDataPacket *pkt, int msecs);
    QByteArray getSentCmd();
    QByteArray getRecvCmd();

protected:
    void devData(IP_Rtu_Recv *pkt, sDataPacket *packet);
    void dataUnit(int i, IP_sDataUnit &rtu, sDataUnit &data);
    void devLine(IP_RtuRecvLine &rtuData, sDevData &data);
    void envData(IP_RtuRecvLine &rtuData, sEnvData &data);

private:
    uchar *mSentBuf, *mRecvBuf;
    int mSentLen, mRecvLen;

    SerialPort *mSerial;
    QMutex *mMutex;
    bool isRun;

    IP_Rtu_Recv *mRtuPkt;
    IP_RtuSent *mRtuSent;
    IP_RtuRecv *mRtuRecv;
};

#endif // IP_RTUTRANS_H
