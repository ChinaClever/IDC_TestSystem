#ifndef BUS_RTUTRANS_H
#define BUS_RTUTRANS_H
#include "bus_rturecv.h"
#include "bus_com/buspacketsi.h"

class BUS_RtuTrans
{
public:
    BUS_RtuTrans();

    void init(SerialPort *serial);
    int transmit(int addr, sBoxData *box, int msecs); //发送数据并回收
    bool sentSetCmd(int addr, int reg, ushort value, int msecs);
    QByteArray getSentCmd();

protected:
    int transData(int addr, BUS_RtuRecv *pkt, int msecs);
    void loopObjData(BUS_sObjUnit *loop, BUS_RtuRecvLine *data);
    void loopData(sBoxData *box, BUS_RtuRecv *pkt);
    void envData(sBoxData *box, BUS_RtuRecv *pkt);

private:
    uchar *mBuf;
    int mLen;

    SerialPort *mSerial;
    QMutex *mMutex;
    bool isRun;

    BUS_RtuRecv *mRtuPkt;
    BUS_RtuSent *mRtuSent;
};

#endif // BUS_RTUTRANS_H
