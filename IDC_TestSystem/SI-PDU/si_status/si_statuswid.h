#ifndef SI_STATUSWID_H
#define SI_STATUSWID_H

#include "tablewid/linethresholdtablewid.h"
#include "tablewid/transtablewid.h"
#include "si_com/sidatapackets.h"

namespace Ui {
class SI_StatusWid;
}

class SI_StatusWid : public QWidget
{
    Q_OBJECT

public:
    explicit SI_StatusWid(QWidget *parent = 0);
    ~SI_StatusWid();

public slots:
    void simulateSlot(int);

protected slots:
     void initFunSLot();

private:
    Ui::SI_StatusWid *ui;

    LineTableWid *mDevTableWid;
    EnvTableWid *mEnvTableWid;
    LineThresholdTableWid *mThresholdTableWid;
    TransTableWid *mTransTableWid;
};

#endif // SI_STATUSWID_H
