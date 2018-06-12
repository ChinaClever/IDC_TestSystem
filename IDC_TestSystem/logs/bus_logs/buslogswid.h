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

private:
    Ui::BusLogsWid *ui;
};

#endif // BUSLOGSWID_H
