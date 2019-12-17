#ifndef M_RTUTHREAD_H
#define M_RTUTHREAD_H

#include "m_com/m_datapackets.h"
#include "m_dp/m_dpthread.h"
#include "rtucom/rtuthread.h"
#include "m_rtutrans.h"

class M_RtuThread : public RtuThread
{
    Q_OBJECT
    explicit M_RtuThread(QObject *parent = nullptr);
public:
    static M_RtuThread *bulid(QObject *parent = nullptr);

protected:
    void workDown();
    void writeErrCmd(int id);

private slots:
    void initSlot();

private:
    M_RtuTrans *mRtu;
};

#endif // M_RTUTHREAD_H
