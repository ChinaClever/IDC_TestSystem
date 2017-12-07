#ifndef SI_RECORDLOGTHREAD_H
#define SI_RECORDLOGTHREAD_H

#include "si_envlogthread.h"

class SI_RecordLogThread : public SI_ComLogThread
{
    Q_OBJECT
public:
    explicit SI_RecordLogThread(QObject *parent = nullptr);

protected:
    void saveLogs();
    void saveLogItem(int id);
};

#endif // SI_RECORDLOGTHREAD_H
