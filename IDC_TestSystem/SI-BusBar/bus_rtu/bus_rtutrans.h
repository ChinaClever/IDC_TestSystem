#ifndef BUS_RTUTRANS_H
#define BUS_RTUTRANS_H
#include "bus_rturecv.h"
#include "bus_com/buspacketsi.h"

class BUS_RtuTrans: public QThread
{
    explicit BUS_RtuTrans(QObject *parent = nullptr);
public:
    static BUS_RtuTrans *bulid(QObject *parent = nullptr);
    ~BUS_RtuTrans();

    void init(SerialPort *serial);
    int transmit(int addr, sDataPacket *box, int msecs); //发送数据并回收
    bool sentSetCmd(int addr, int reg, ushort value, int msecs);
    QByteArray getSentCmd();
    QByteArray getRecvCmd();

    bool sentCmd(sRtuSentCom &cmd);
protected:
    int transData(int addr, BUS_RtuRecv *pkt, int msecs);
    void loopObjData(sObjData *loop, BUS_RtuRecvLine *data);
    void loopData(sDevData *box, BUS_RtuRecv *pkt);
    void envData(sDataPacket *box, BUS_RtuRecv *pkt);
    void sentCmdList();

private:
    uchar *mSentBuf, *mRecvBuf;
    int mSentLen, mRecvLen;

    SerialPort *mSerial;
    QMutex *mMutex;
    bool isRun;

    BUS_RtuRecv *mRtuPkt;
    BUS_RtuSent *mRtuSent;
    QList<sRtuSentCom> mCmdList;
};

#endif // BUS_RTUTRANS_H
