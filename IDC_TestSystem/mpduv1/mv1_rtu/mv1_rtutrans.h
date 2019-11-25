#ifndef MV1_RTUTRANS_H
#define MV1_RTUTRANS_H
#include "mv1_rturecv.h"
#include "rtutrans.h"

class MV1_RtuTrans : public RtuTrans
{
    MV1_RtuTrans();
public:
    static MV1_RtuTrans *bulid();

    void init(SerialPort *serial);
    bool sentSetCmd(int addr, int reg, ushort value, int msecs);
    int transData(int addr, int cmd, sDataPacket *pkt, int msecs);

    QByteArray getSentCmd();
    QByteArray getRecvCmd();

protected:
    void getAlarm(sDataUnit &data);
    void dataUnit(int i, ZM_sDataUnit &rtu, sDataUnit &data);
    void devObjData(ZM_sObjData &rtuData, int i, sObjData &data);
    void devData(ZM_sRtuPacket &rtuData, sDevData &data);
    void envData(ZM_sRtuPacket &rtuData, sEnvData &data);
    void devDataPacket(ZM_sRtuRecv *pkt, sDataPacket *packet);

    int transData(int addr, ushort reg, ushort len, ZM_sRtuRecv *pkt, int msecs);

private:
    uchar *mSentBuf, *mRecvBuf;
    int mSentLen, mRecvLen;

    SerialPort *mSerial;
    QMutex *mMutex;
    bool isRun;

    ZM_sRtuRecv *mRtuPkt;
    MV1_RtuSent *mRtuSent;
    MV1_RtuRecv *mRtuRecv;
};

#endif // MV1_RTUTRANS_H
