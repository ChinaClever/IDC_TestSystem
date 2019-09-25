#ifndef SI_RTUTHREAD_H
#define SI_RTUTHREAD_H

#include "si_rtutrans.h"
#include "si_com/sidatapackets.h"
#include "si_dp/si_dpthread.h"

class SI_RtuThread : public RtuThread
{
    Q_OBJECT
    explicit SI_RtuThread(QObject *parent = nullptr);
public:
    static SI_RtuThread *bulid(QObject *parent = nullptr);

protected:
    void workDown();
    void writeErrCmd(int id);

protected slots:
    void initSlot();

protected:
    SI_RtuTrans *mRtu;
};

#endif // SI_RTUTHREAD_H
