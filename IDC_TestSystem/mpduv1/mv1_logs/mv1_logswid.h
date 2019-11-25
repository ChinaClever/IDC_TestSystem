#ifndef MV1_LOGSWID_H
#define MV1_LOGSWID_H

#include "mv1_logoutputrecordwid.h"
#include "mv1_com/mv1_datapackets.h"

namespace Ui {
class MV1_LogsWid;
}

class MV1_LogsWid : public QWidget
{
    Q_OBJECT

public:
    explicit MV1_LogsWid(QWidget *parent = 0);
    ~MV1_LogsWid();

signals:
     void updateSig();

public slots:
    void updateWidSlot(int);

protected slots:
     void initFunSLot();

private:
    Ui::MV1_LogsWid *ui;

    MV1_LogAlarmWid *mLogAlarmWid;
    MV1_LogEnvWid *mLogEnvWid;
    MV1_LogModbusCmdWid *mLogModbusCmdWid;
    MV1_LogModbusTransWid *mLogModbusTransWid;
    MV1_LogLineRecordWid *mLogRealRecordWid;
    MV1_LogLineThresholdWid *mLogThresholdWid;
    MV1_LogOutputRecordWid *mLogOutputWid;
};

#endif // MV1_LOGSWID_H
