#ifndef RSET_RTUTHREAD_H
#define RSET_RTUTHREAD_H

#include "r_rtu/r_rtutrans.h"


class RSet_RtuThread : public QThread
{
    Q_OBJECT
public:
    explicit RSet_RtuThread(QObject *parent = nullptr);
    ~RSet_RtuThread();

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
    R_RtuTrans *mRtu;

    QList<sRtuSetCmd> mList;
};

#endif // RSET_RTUTHREAD_H
