#ifndef Z_SIMULATETHREAD_H
#define Z_SIMULATETHREAD_H
#include "z_com/z_datapackets.h"
#include "z_dp/z_dpthread.h"
#include "tablewid/simulatethread.h"
#include "z_rtu/z_rtutrans.h"

class Z_SimulateThread : public SimulateThread
{
    Q_OBJECT
public:
    explicit Z_SimulateThread(QObject *parent = nullptr);

protected:
    void workDown();
    void writeErrCmd(int id);

private slots:
    void initSlot();

private:
    Z_RtuTrans *mRtu;
};


#endif // Z_SIMULATETHREAD_H
