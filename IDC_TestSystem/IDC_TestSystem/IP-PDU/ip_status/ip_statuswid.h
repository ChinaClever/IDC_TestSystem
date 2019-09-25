#ifndef IP_STATUSWID_H
#define IP_STATUSWID_H

#include "tablewid/linethresholdtablewid.h"
#include "tablewid/envtablewid.h"
#include "tablewid/transtablewid.h"


namespace Ui {
class IP_StatusWid;
}

class IP_StatusWid : public QWidget
{
    Q_OBJECT

public:
    explicit IP_StatusWid(QWidget *parent = 0);
    ~IP_StatusWid();

public slots:
    void simulateSlot(int);

protected slots:
     void initFunSLot();

private:
    Ui::IP_StatusWid *ui;

    LineTableWid *mDevTableWid;
    EnvTableWid *mEnvTableWid;

    LineThresholdTableWid *mThresholdTableWid;
    TransTableWid *mTransTableWid;
};

#endif // IP_STATUSWID_H
