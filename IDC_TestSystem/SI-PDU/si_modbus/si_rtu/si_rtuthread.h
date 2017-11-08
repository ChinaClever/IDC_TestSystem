#ifndef SI_RTUTHREAD_H
#define SI_RTUTHREAD_H

#include "si_rtu_recv.h"

#define RTU_BUF_SIZE 512

class SI_RtuThread : public QThread
{
    Q_OBJECT
    explicit SI_RtuThread(QObject *parent = nullptr);

public:
    static SI_RtuThread *bulid(QObject *parent = nullptr);
    ~SI_RtuThread();

    void init(SerialPort *serial);
    bool sentSetCmd(uchar addr, uchar reg, ushort value);

protected:
    void run();
    void transData(int addr, int line);

signals:

public slots:

private:
    uchar *mBuf;
    SerialPort *mSerial;
    SI_Rtu_Recv *mRtuPkt;
    QMutex *mMutex;
    bool isRun;

    SI_RtuSent *mRtuSent;
    SI_RtuRecv *mRtuRecv;
};

#endif // SI_RTUTHREAD_H
