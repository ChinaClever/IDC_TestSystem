#ifndef BUSLOGSWID_H
#define BUSLOGSWID_H

#include "buslogthresholdwid.h"

namespace Ui {
class BusLogsWid;
}

class BusLogsWid : public QWidget
{
    Q_OBJECT

public:
    explicit BusLogsWid(QWidget *parent = 0);
    ~BusLogsWid();

signals:
     void updateSig();

public slots:
    void updateWidSlot(int);

protected slots:
     void initFunSLot();

private:
    Ui::BusLogsWid *ui;

    BusLogAlarmWid *mLogAlarmWid;
    BusLogEnvWid *mLogEnvWid;
    BusLogModbusCmdWid *mLogModbusCmdWid;
    BusLogModbusTransWid *mLogModbusTransWid;
    BusLogRealRecordWid *mLogRealRecordWid;
    BusLogThresholdWid *mLogThresholdWid;
};

#endif // BUSLOGSWID_H
