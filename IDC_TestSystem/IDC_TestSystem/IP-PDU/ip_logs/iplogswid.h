#ifndef IPLOGSWID_H
#define IPLOGSWID_H

#include "iplogthresholdwid.h"

namespace Ui {
class IpLogsWid;
}

class IpLogsWid : public QWidget
{
    Q_OBJECT

public:
    explicit IpLogsWid(QWidget *parent = 0);
    ~IpLogsWid();

signals:
     void updateSig();

public slots:
    void updateWidSlot(int);

protected slots:
     void initFunSLot();

private:
    Ui::IpLogsWid *ui;

    IpLogAlarmWid *mLogAlarmWid;
    IpLogEnvWid *mLogEnvWid;
    IpLogModbusCmdWid *mLogModbusCmdWid;
    IpLogModbusTransWid *mLogModbusTransWid;
    IpLogRealRecordWid *mLogRealRecordWid;
    IpLogThresholdWid *mLogThresholdWid;
};

#endif // IPLOGSWID_H
