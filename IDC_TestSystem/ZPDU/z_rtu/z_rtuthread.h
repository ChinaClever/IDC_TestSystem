#ifndef Z_RTUTHREAD_H
#define Z_RTUTHREAD_H

#include "z_com/z_datapackets.h"
#include "z_dp/z_dpthread.h"
#include "rtucom/rtuthread.h"
#include "z_rtutrans.h"

class Z_RtuThread : public RtuThread
{
    Q_OBJECT
public:
    explicit Z_RtuThread(QObject *parent = nullptr);

protected:
    void workDown();
    void writeErrCmd(int id);

private slots:
    void initSlot();

private:
    Z_RtuTrans *mRtu;
};


#endif // Z_RTUTHREAD_H
