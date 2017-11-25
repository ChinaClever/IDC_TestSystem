#ifndef SI_SIMULATETHREAD_H
#define SI_SIMULATETHREAD_H

#include "si_com/sidatapackets.h"

class SI_SimulateThread : public QThread
{
    Q_OBJECT
public:
    explicit SI_SimulateThread(QObject *parent = nullptr);
    ~SI_SimulateThread();

protected:
    void run();
    void init();
    void workDown();

signals:

public slots:
    void startThread();
    void stopThread();

private:
    bool isRun;

    SIDataPackets *mPackets;
    SI_RtuThread *mRtu;
};

#endif // SI_SIMULATETHREAD_H
