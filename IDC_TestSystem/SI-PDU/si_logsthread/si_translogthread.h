#ifndef SI_TRANSLOGTHREAD_H
#define SI_TRANSLOGTHREAD_H

#include "si_comlogthread.h"

class SI_TransLogThread : public SI_ComLogThread
{
    Q_OBJECT
public:
    explicit SI_TransLogThread(QObject *parent = nullptr);

protected:
    void saveLogs();
    void saveLogItem(int id);
};

#endif // SI_TRANSLOGTHREAD_H
