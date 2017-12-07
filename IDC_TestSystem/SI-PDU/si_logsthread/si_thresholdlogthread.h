#ifndef SI_THRESHOLDLOGTHREAD_H
#define SI_THRESHOLDLOGTHREAD_H

#include "si_recordlogthread.h"

class SI_ThresholdLogThread : public SI_ComLogThread
{
    Q_OBJECT
public:
    explicit SI_ThresholdLogThread(QObject *parent = nullptr);

protected:
    void saveLogs();
    void saveLogItem(int id);
};

#endif // SI_THRESHOLDLOGTHREAD_H
