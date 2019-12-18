#ifndef M_RTUTRANS_H
#define M_RTUTRANS_H
#include "m_rturecv.h"
#include "rtutrans.h"

class M_RtuTrans : public RtuTrans
{
    M_RtuTrans();
public:
    static M_RtuTrans *bulid();

    void init(SerialPort *serial);
    bool sentSetCmd(int addr, int reg, ushort value, int msecs);
    int transData(int addr, int cmd, sDataPacket *pkt, int msecs);

    QByteArray getSentCmd();
    QByteArray getRecvCmd();
    void devData(ZM_sRtuPacket &rtuData, sDevData &data);

protected:
    int transData(int addr, ushort reg, ushort len, ZM_sRtuRecv *pkt, int msecs);

private:
    uchar *mSentBuf, *mRecvBuf;
    int mSentLen, mRecvLen;

    SerialPort *mSerial;
    QMutex *mMutex;
    bool isRun;

    ZM_sRtuRecv *mRtuPkt;
    M_RtuSent *mRtuSent;
    M_RtuRecv *mRtuRecv;
};

#endif // M_RTUTRANS_H
