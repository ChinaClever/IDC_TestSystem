#ifndef ZSET_RTUTHREAD_H
#define ZSET_RTUTHREAD_H

#include "z_rtu/z_rtutrans.h"

struct sZTestRtuSetCmd
{
    ushort addr;
    ushort reg;
    ushort value;
};

class ZSet_RtuThread : public QThread
{
    Q_OBJECT
public:
    explicit ZSet_RtuThread(QObject *parent = nullptr);
    ~ZSet_RtuThread();

    void setCmd(const sZTestRtuSetCmd &cmd) {mList.append(cmd);}
    int mReg;

protected:
    bool sentSetCmd(int addr, int reg, ushort value, int msecs);
    void run();

signals:
    void cmdSig(QString);

public slots:

private:
    bool isRun;
    QMutex *mMutex;
    Z_RtuTrans *mRtu;

    QList<sZTestRtuSetCmd> mList;
};

#endif // ZSET_RTUTHREAD_H
