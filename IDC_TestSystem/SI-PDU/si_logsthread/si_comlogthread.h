#ifndef SI_COMLOGTHREAD_H
#define SI_COMLOGTHREAD_H

#include "si_com/sidatapackets.h"

class SI_ComLogThread : public QThread
{
    Q_OBJECT
public:
    explicit SI_ComLogThread(QObject *parent = nullptr);
    ~SI_ComLogThread();

protected:
    void run();
    void workDown();
    virtual void saveLogs()=0;
    sDataPacket *getPacket(int id);

    void startThread();
    void stopThread();

signals:

public slots:
    void toolBoxSlot(int id);

protected slots:
    void timeoutDone();

protected:
    bool isRun;
    QTimer *timer;
    int mCount;
};

#endif // SI_COMLOGTHREAD_H
