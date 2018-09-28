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
    int transData(int addr, int cmd, sDataPacket *pkt, int msecs);

    QByteArray getSentCmd();
    QByteArray getRecvCmd();

protected:
    void getAlarm(sDataUnit &data);
    void dataUnit(int i, Z_sDataUnit &rtu, sDataUnit &data, int rate=1);
    void devObjData(Z_sObjData &rtuData, int i, sObjData &data);
    void devData(Z_sRtuPacket &rtuData, sDevData &data);
    void envData(Z_sEnv &rtuData, sEnvData &data);
    void devDataPacket(Z_sRtuRecv *pkt, sDataPacket *packet);

    int transData(int addr, ushort reg, ushort len, Z_sRtuRecv *pkt, int msecs);

private:
    uchar *mSentBuf, *mRecvBuf;
    int mSentLen, mRecvLen;

    SerialPort *mSerial;
    QMutex *mMutex;
    bool isRun;

    Z_sRtuRecv *mRtuPkt;
    Z_RtuSent *mRtuSent;
    Z_RtuRecv *mRtuRecv;
};

#endif // Z_RTUTRANS_H
