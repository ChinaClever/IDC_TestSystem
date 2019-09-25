#ifndef Z_LOGSWID_H
#define Z_LOGSWID_H

#include "z_loglooprecordwid.h"
#include "z_com/z_datapackets.h"

namespace Ui {
class Z_LogsWid;
}

class Z_LogsWid : public QWidget
{
    Q_OBJECT

public:
    explicit Z_LogsWid(QWidget *parent = 0);
    ~Z_LogsWid();

signals:
     void updateSig();

public slots:
    void updateWidSlot(int);

protected slots:
     void initFunSLot();

private:
    Ui::Z_LogsWid *ui;

    Z_LogAlarmWid *mLogAlarmWid;
    Z_LogEnvWid *mLogEnvWid;
    Z_LogModbusCmdWid *mLogModbusCmdWid;
    Z_LogModbusTransWid *mLogModbusTransWid;
    Z_LogLineRecordWid *mLogRealRecordWid;
    Z_LogLineThresholdWid *mLogThresholdWid;
    Z_LogOutputRecordWid *mLogOutputWid;
    Z_LogLoopRecordWid *mLogLoopWid;
};

#endif // Z_LOGSWID_H
