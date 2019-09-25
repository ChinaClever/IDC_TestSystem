#ifndef SILOGSWID_H
#define SILOGSWID_H

#include "silogalarmwid.h"

namespace Ui {
class SILogsWid;
}

class SILogsWid : public QWidget
{
    Q_OBJECT

public:
    explicit SILogsWid(QWidget *parent = 0);
    ~SILogsWid();

signals:
     void updateSig();

public slots:
    void updateWidSlot(int);

protected slots:
     void initFunSLot();

private:
    Ui::SILogsWid *ui;

    SiLogEnvWid *mLogEnvWid;
    SiLogAlarmWid *mLogAlarmWid;
    SiLogModbusCmdWid *mLogModbusCmdWid;
    SiLogModbusTransWid *mLogModbusTransWid;
    SiLogRealRecordWid *mLogRealRecordWid;
    SiLogThresholdWid *mLogThresholdWid;
};

#endif // SILOGSWID_H
