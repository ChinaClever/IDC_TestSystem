#ifndef R_RTUTRANS_H
#define R_RTUTRANS_H
#include "r_rturecv.h"
#include "rtucom/rtutrans.h"

class R_RtuTrans : public RtuTrans
{
    R_RtuTrans();
public:
    static R_RtuTrans *bulid();

    void init(SerialPort *serial);
    bool sentSetCmd(int addr, int reg, ushort value, int msecs);

    QByteArray getSentCmd();
    QByteArray getRecvCmd();

    int transData(int addr, int cmd, sDataPacket *pkt, int msecs);

protected:
    int transData(int addr, ushort reg, ushort len, ZM_sRtuRecv *pkt, int msecs);
    void getAlarm(sDataUnit &data);
    void dataUnit(int i, ZM_sDataUnit &rtu, sDataUnit &data, int rate=1);
    void devObjData(ZM_sObjData &rtuData, int i, sObjData &data , bool flag);
    void devData(ZM_sRtuPacket &rtuData, sDevData &data);
    void envData(ZM_sEnv &rtuData, sEnvData &data);
    void devDataPacket(ZM_sRtuRecv *pkt, sDataPacket *packet);


private:
    uchar *mSentBuf, *mRecvBuf;
    int mSentLen, mRecvLen;

    SerialPort *mSerial;
    QMutex *mMutex;
    bool isRun;

    ZM_sRtuRecv *mRtuPkt;
    R_RtuSent *mRtuSent;
    R_RtuRecv *mRtuRecv;
};

#endif // R_RTUTRANS_H
