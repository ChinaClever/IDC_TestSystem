#ifndef SI_SIMULATETHREAD_H
#define SI_SIMULATETHREAD_H

#include "si_dp/si_dpthread.h"
#include "tablewid/simulatethread.h"

class SI_SimulateThread : public SimulateThread
{
    Q_OBJECT
public:
    explicit SI_SimulateThread(QObject *parent = nullptr);

protected:
    void workDown();
    void writeErrCmd(int id);

protected slots:
    void initSlot();

protected:
    SI_RtuThread *mRtu;
};

#endif // SI_SIMULATETHREAD_H
