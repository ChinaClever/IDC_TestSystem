#ifndef MTEST_RTUTHREAD_H
#define MTEST_RTUTHREAD_H

#include "m_rtu/m_rtutrans.h"


class MTest_RtuThread : public QThread
{
    Q_OBJECT
public:
    explicit MTest_RtuThread(QObject *parent = nullptr);
    ~MTest_RtuThread();

    void setCmd(const sRtuSetCmd &cmd) {mList.append(cmd);}
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

    QList<sRtuSetCmd> mList;
};

#endif // MTEST_RTUTHREAD_H
