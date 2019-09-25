#ifndef ELOAD_LOGSWID_H
#define ELOAD_LOGSWID_H

#include "eload_logmodbustranswid.h"

namespace Ui {
class ELoad_LogsWid;
}

class ELoad_LogsWid : public QWidget
{
    Q_OBJECT

public:
    explicit ELoad_LogsWid(QWidget *parent = 0);
    ~ELoad_LogsWid();

signals:
     void updateSig();

public slots:
    void updateWidSlot(int);

protected slots:
     void initFunSLot();

private:
    Ui::ELoad_LogsWid *ui;

    ELoad_LogAlarmWid *mLogAlarmWid;
    ELoad_LogEnvWid *mLogEnvWid;
    ELoad_LogModbusCmdWid *mLogModbusCmdWid;
    ELoad_LogModbusTransWid *mLogModbusTransWid;
    ELoad_LogLineRecordWid *mLogRealRecordWid;
    ELoad_LogLineThresholdWid *mLogThresholdWid;
};

#endif // ELOAD_LOGSWID_H
