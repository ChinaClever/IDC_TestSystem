#ifndef SI_ALARMLOGTHREAD_H
#define SI_ALARMLOGTHREAD_H

#include <QThread>
#include "si_com/sidatapackets.h"

class SI_AlarmLogThread : public QThread
{
    Q_OBJECT
    explicit SI_AlarmLogThread(QObject *parent = nullptr);

public:
    static SI_AlarmLogThread *bulid();
    void saveAlarm(int id);

protected:
    void saveMsg(int id, int line, const QString &typeStr, const QString &str);
    void unitAlarm(int id, int i, const QString &str, sDataUnit &unit, double rate, const QString &sym);
};

#endif // SI_ALARMLOGTHREAD_H
