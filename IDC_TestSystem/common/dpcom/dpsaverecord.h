#ifndef DPSLAVERECORD_H
#define DPSLAVERECORD_H

#include "datapacket.h"
#include "sqlcom/dblinethresholds.h"

class DpSaveRecord : public QThread
{
    Q_OBJECT
public:
    explicit DpSaveRecord(QObject *parent = nullptr);
    ~DpSaveRecord();

    void run();
    void initPackets(sDevPackets *packets) { mPackets = packets; }
protected:
    virtual void saveLogs();
    virtual void saveLogItem(int id)=0;

protected:
    bool isRun;
    sDevPackets *mPackets;
    int mSwValue;  // 开关状态，开的值 默认为1
};

#endif // DPSLAVERECORD_H
