#ifndef M_SIMULATETHREAD_H
#define M_SIMULATETHREAD_H

#include "m_com/m_datapackets.h"
#include "m_dp/m_dpthread.h"
#include "tablewid/simulatethread.h"
#include "m_rtu/m_rtutrans.h"

class M_SimulateThread : public SimulateThread
{
    Q_OBJECT
public:
    explicit M_SimulateThread(QObject *parent = nullptr);

protected:
    void workDown();
    void writeErrCmd(int id);

private slots:
    void initSlot();

private:
    M_RtuTrans *mRtu;
};

#endif // M_SIMULATETHREAD_H
