#ifndef MV1_RTUTHREAD_H
#define MV1_RTUTHREAD_H

#include "mv1_com/mv1_datapackets.h"
#include "mv1_dp/mv1_dpthread.h"
#include "rtucom/rtuthread.h"
#include "mv1_rtutrans.h"

class MV1_RtuThread : public RtuThread
{
    Q_OBJECT
    explicit MV1_RtuThread(QObject *parent = nullptr);
public:
    static MV1_RtuThread *bulid(QObject *parent = nullptr);

protected:
    void workDown();
    void writeErrCmd(int id);

private slots:
    void initSlot();

private:
    MV1_RtuTrans *mRtu;
};

#endif // MV1_RTUTHREAD_H
