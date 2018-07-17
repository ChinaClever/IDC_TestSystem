#ifndef IP_SIMULATEWID_H
#define IP_SIMULATEWID_H

#include "ip_devtablewid.h"

namespace Ui {
class IP_SimulateWid;
}

class IP_SimulateWid : public QWidget
{
    Q_OBJECT

public:
    explicit IP_SimulateWid(QWidget *parent = 0);
    ~IP_SimulateWid();

private:
    Ui::IP_SimulateWid *ui;
};

#endif // IP_SIMULATEWID_H
