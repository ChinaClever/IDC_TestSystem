#ifndef MV1SET_RTUTHREAD_H
#define MV1SET_RTUTHREAD_H

#include "mv1_rtu/mv1_rtutrans.h"


class MV1Set_RtuThread : public QThread
{
    Q_OBJECT
public:
    explicit MV1Set_RtuThread(QObject *parent = nullptr);
    ~MV1Set_RtuThread();

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
    MV1_RtuTrans *mRtu;

    QList<sRtuSetCmd> mList;
};

#endif // MV1SET_RTUTHREAD_H
