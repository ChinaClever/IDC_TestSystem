#ifndef IP_DPSLAVERECORD_H
#define IP_DPSLAVERECORD_H

#include "ip_com/ipdatapackets.h"

class IP_DpSlaveRecord : public QThread
{
    Q_OBJECT
public:
    explicit IP_DpSlaveRecord(QObject *parent = nullptr);
    ~IP_DpSlaveRecord();

    void run();
protected:
    virtual void saveLogs();
    virtual void saveLogItem(int id);

protected:
    bool isRun;
};

#endif // IP_DPSLAVERECORD_H
