#ifndef R_LOGSWID_H
#define R_LOGSWID_H

#include "r_loglooprecordwid.h"
#include "r_com/r_datapackets.h"

namespace Ui {
class R_LogsWid;
}

class R_LogsWid : public QWidget
{
    Q_OBJECT

public:
    explicit R_LogsWid(QWidget *parent = 0);
    ~R_LogsWid();

signals:
     void updateSig();

public slots:
    void updateWidSlot(int);

protected slots:
     void initFunSLot();

private:
    Ui::R_LogsWid *ui;

    R_LogAlarmWid *mLogAlarmWid;
    R_LogEnvWid *mLogEnvWid;
    R_LogModbusCmdWid *mLogModbusCmdWid;
    R_LogModbusTransWid *mLogModbusTransWid;
    R_LogLineRecordWid *mLogRealRecordWid;
    R_LogLineThresholdWid *mLogThresholdWid;
    R_LogOutputRecordWid *mLogOutputWid;
    R_LogLoopRecordWid *mLogLoopWid;
};

#endif // R_LOGSWID_H
