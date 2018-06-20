#ifndef MPDURTUTESTTHREAD_H
#define MPDURTUTESTTHREAD_H
#include "mpdurtutestsent.h"

struct sMpduRtuTestSetCmd
{
    int addr;
    int reg;
    ushort value;
};


class MpduRtuTestThread : public QThread
{
    Q_OBJECT
public:
    explicit MpduRtuTestThread(QObject *parent = nullptr);
    ~MpduRtuTestThread();

    void init(SerialPort *serial);
    void setCmd(sMpduRtuTestSetCmd &cmd) {mList.append(cmd);}
    int mReg;

protected:
    bool sentSetCmd(int addr, int reg, ushort value, int msecs);
    void run();

signals:
    void cmdSig(QString);

public slots:

private:
    bool isRun;
    uchar *mBuf;
    SerialPort *mSerial;
    QMutex *mMutex;
    MpduRtuTestSent *mRtuSent;

    QList<sMpduRtuTestSetCmd> mList;
};

#endif // MPDURTUTESTTHREAD_H
