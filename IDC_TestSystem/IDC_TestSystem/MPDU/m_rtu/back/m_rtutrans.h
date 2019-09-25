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

protected:
    void getAlarm(sDataUnit &data);
    void dataUnit(int i, M_sDataUnit &rtu, sDataUnit &data);
    void devObjData(M_sObjData &rtuData, int i, sObjData &data);
    void devData(M_sRtuPacket &rtuData, sDevData &data);
    void envData(M_sRtuPacket &rtuData, sEnvData &data);
    void devDataPacket(M_sRtuRecv *pkt, sDataPacket *packet);

    int transData(int addr, ushort reg, ushort len, M_sRtuRecv *pkt, int msecs);

private:
    uchar *mSentBuf, *mRecvBuf;
    int mSentLen, mRecvLen;

    SerialPort *mSerial;
    QMutex *mMutex;
    bool isRun;

    M_sRtuRecv *mRtuPkt;
    M_RtuSent *mRtuSent;
    M_RtuRecv *mRtuRecv;
};

#endif // M_RTUTRANS_H
