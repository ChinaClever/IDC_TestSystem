#ifndef SI_ENVLOGTHREAD_H
#define SI_ENVLOGTHREAD_H

#include "si_translogthread.h"

class SI_EnvLogThread : public SI_ComLogThread
{
    Q_OBJECT
public:
    explicit SI_EnvLogThread(QObject *parent = nullptr);

protected:
    void saveLogs();
    void saveLogItem(int id);
};

#endif // SI_ENVLOGTHREAD_H
