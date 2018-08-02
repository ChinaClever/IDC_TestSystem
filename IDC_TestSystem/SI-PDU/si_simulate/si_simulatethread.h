#ifndef SI_SIMULATETHREAD_H
#define SI_SIMULATETHREAD_H

#include "si_dp/si_dpthread.h"

class SI_SimulateThread : public QThread
{
    Q_OBJECT
public:
    explicit SI_SimulateThread(QObject *parent = nullptr);
    ~SI_SimulateThread();

protected:
    void run();    
    void workDown();
    void sentOkCmd(sRtuCount &count);
    void saveErrCmd(int id, sRtuCount &count);
    void setOffLine();
    void clearCount();

signals:

public slots:
    void startThread();
    void stopThread();

private slots:
    void initSlot();

private:
    bool isRun;

    SI_DpThread *mDpThread;
    sDevPackets *mPackets;
    SI_RtuThread *mRtu;
};

#endif // SI_SIMULATETHREAD_H
