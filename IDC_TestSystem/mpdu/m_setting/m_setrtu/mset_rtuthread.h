#ifndef MSET_RTUTHREAD_H
#define MSET_RTUTHREAD_H

#include "m_rtu/m_rtutrans.h"

struct sMTestRtuSetCmd
{
    int addr;
    int reg;
    ushort value;
};


class MSet_RtuThread : public QThread
{
    Q_OBJECT
public:
    explicit MSet_RtuThread(QObject *parent = nullptr);
    ~MSet_RtuThread();

    void setCmd(const sMTestRtuSetCmd &cmd) {mList.append(cmd);}
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
    M_RtuTrans *mRtu;

    QList<sMTestRtuSetCmd> mList;
};

#endif // MSET_RTUTHREAD_H
