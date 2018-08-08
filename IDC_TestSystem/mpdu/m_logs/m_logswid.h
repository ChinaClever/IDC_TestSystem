#ifndef M_LOGSWID_H
#define M_LOGSWID_H

#include "m_logoutputrecordwid.h"
#include "m_com/m_datapackets.h"

namespace Ui {
class M_LogsWid;
}

class M_LogsWid : public QWidget
{
    Q_OBJECT

public:
    explicit M_LogsWid(QWidget *parent = 0);
    ~M_LogsWid();

signals:
     void updateSig();

public slots:
    void updateWidSlot(int);

protected slots:
     void initFunSLot();

private:
    Ui::M_LogsWid *ui;

    M_LogAlarmWid *mLogAlarmWid;
    M_LogEnvWid *mLogEnvWid;
    M_LogModbusCmdWid *mLogModbusCmdWid;
    M_LogModbusTransWid *mLogModbusTransWid;
    M_LogLineRecordWid *mLogRealRecordWid;
    M_LogLineThresholdWid *mLogThresholdWid;
    M_LogOutputRecordWid *mLogOutputWid;
};

#endif // M_LOGSWID_H
