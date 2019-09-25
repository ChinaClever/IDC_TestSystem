#ifndef R_STATUSWID_H
#define R_STATUSWID_H

#include "r_com/r_datapackets.h"
#include "tablewid/linethresholdtablewid.h"
#include "tablewid/envtablewid.h"
#include "tablewid/transtablewid.h"
#include "tablewid/looptablewid.h"
#include "tablewid/loopthresholdtablewid.h"

namespace Ui {
class R_StatusWid;
}

class R_StatusWid : public QWidget
{
    Q_OBJECT

public:
    explicit R_StatusWid(QWidget *parent = 0);
    ~R_StatusWid();

public slots:
    void simulateSlot(int);

protected slots:
     void initFunSLot();

private:
    Ui::R_StatusWid *ui;

    LineTableWid *mDevTableWid;
    EnvTableWid *mEnvTableWid;
    LoopTableWid *mLoopTableWid;
    LoopThresholdTableWid *mLoopThresholdTableWid;

    OutputTableWid *mOutputTableWid;
    OutputThresholdTableWid *mOutputThresholdTableWid;
    LineThresholdTableWid *mThresholdTableWid;
    TransTableWid *mTransTableWid;
};

#endif // R_STATUSWID_H
