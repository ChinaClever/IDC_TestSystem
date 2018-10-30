#ifndef Z_RTUTRANS_H
#define Z_RTUTRANS_H
#include "z_rturecv.h"
#include "rtucom/rtutrans.h"

class Z_RtuTrans : public RtuTrans
{
    Z_RtuTrans();
public:
    static Z_RtuTrans *bulid();

    void init(SerialPort *serial);
    bool sentSetCmd(int addr, int reg, ushort value, int msecs);

    QByteArray getSentCmd();
    QByteArray getRecvCmd();

    int transData(int addr, int cmd, sDataPacket *pkt, int msecs);

protected:
    int transData(int addr, ushort reg, ushort len, ZM_sRtuRecv *pkt, int msecs);

private:
    uchar *mSentBuf, *mRecvBuf;
    int mSentLen, mRecvLen;

    SerialPort *mSerial;
    QMutex *mMutex;
    bool isRun;

    ZM_sRtuRecv *mRtuPkt;
    Z_RtuSent *mRtuSent;
    Z_RtuRecv *mRtuRecv;
};

#endif // Z_RTUTRANS_H
