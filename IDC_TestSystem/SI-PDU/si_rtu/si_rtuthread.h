#ifndef SI_RTUTHREAD_H
#define SI_RTUTHREAD_H

#include "si_rtu_recv.h"

#define RTU_BUF_SIZE 2*SERIAL_LEN

class SI_RtuThread : public QThread
{
    Q_OBJECT
    explicit SI_RtuThread(QObject *parent = nullptr);

public:
    static SI_RtuThread *bulid(QObject *parent = nullptr);
    ~SI_RtuThread();

    void init(SerialPort *serial);
    bool sentSetCmd(int addr, int reg, ushort value, int msecs);
    int transData(int addr, int line, sDataPacket *pkt, int msecs);
    int transData(int addr, int line, SI_Rtu_Recv *pkt, int msecs);
    QByteArray getSentCmd();
    QByteArray getRecvCmd();

protected:
    void devData(SI_Rtu_Recv *pkt, sDataPacket *packet);
    void dataUnit(int i, SI_sDataUnit &rtu, sDataUnit &data);
    void devLine(SI_RtuRecvLine &rtuData, sDevData &data);
    void envData(SI_RtuRecvLine &rtuData, sEnvData &data);

signals:

public slots:

private:
    uchar *mSentBuf, *mRecvBuf;
    int mSentLen, mRecvLen;

    SerialPort *mSerial;
    QMutex *mMutex;
    bool isRun;

    SI_RtuSent *mRtuSent;
    SI_RtuRecv *mRtuRecv;
    SI_Rtu_Recv *mRtuPkt;
};

#endif // SI_RTUTHREAD_H
