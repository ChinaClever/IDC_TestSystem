#ifndef R_RTUTHREAD_H
#define R_RTUTHREAD_H

#include "r_com/r_datapackets.h"
#include "r_dp/r_dpthread.h"
#include "rtucom/rtuthread.h"
#include "r_rtutrans.h"

class R_RtuThread : public RtuThread
{
    Q_OBJECT
    explicit R_RtuThread(QObject *parent = nullptr);
public:
    static R_RtuThread *bulid(QObject *parent = nullptr);

protected:
    void workDown();
    void writeErrCmd(int id);

private slots:
    void initSlot();

private:
    R_RtuTrans *mRtu;
};


#endif // R_RTUTHREAD_H
