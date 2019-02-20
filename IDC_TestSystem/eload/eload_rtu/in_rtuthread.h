#ifndef IN_RTUTHREAD_H
#define IN_RTUTHREAD_H

#include "rtuthread.h"
#include "in_rtutrans.h"

class IN_RtuThread : public RtuThread
{
    Q_OBJECT
    explicit IN_RtuThread(QObject *parent = nullptr);
public:
    static IN_RtuThread *bulid(QObject *parent = nullptr);
    void sentCmd(sRtuSentCom &cmd);
    void init(SerialPort *serial);

protected:
    void workDown();
    void sentCmdList();
    void writeErrCmd(int id);

protected slots:
    void initSlot();

private:
    IN_RtuTrans *mRtu;
    QList<sRtuSentCom> mCmdList;
};

#endif // IN_RTUTHREAD_H
