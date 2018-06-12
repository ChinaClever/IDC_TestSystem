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

//signals:
//     void updateSig();

//public slots:
//    void simulateSlot(int);

//protected slots:
//     void initFunSLot();
//     void timeoutDone();

private:
    Ui::BusLogsWid *ui;

    BusLogAlarmWid *mLogAlarmWid;
};

#endif // BUSLOGSWID_H
