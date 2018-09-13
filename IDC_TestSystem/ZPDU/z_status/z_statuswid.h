#ifndef Z_STATUSWID_H
#define Z_STATUSWID_H

#include "z_com/z_datapackets.h"
#include "tablewid/linethresholdtablewid.h"
#include "tablewid/envtablewid.h"
#include "tablewid/transtablewid.h"
#include "tablewid/looptablewid.h"
#include "tablewid/loopthresholdtablewid.h"

namespace Ui {
class Z_StatusWid;
}

class Z_StatusWid : public QWidget
{
    Q_OBJECT

public:
    explicit Z_StatusWid(QWidget *parent = 0);
    ~Z_StatusWid();

public slots:
    void simulateSlot(int);

protected slots:
     void initFunSLot();

private:
    Ui::Z_StatusWid *ui;

    LineTableWid *mDevTableWid;
    EnvTableWid *mEnvTableWid;
    LoopTableWid *mLoopTableWid;
    LoopThresholdTableWid *mLoopThresholdTableWid;

    OutputTableWid *mOutputTableWid;
    OutputThresholdTableWid *mOutputThresholdTableWid;
    LineThresholdTableWid *mThresholdTableWid;
    TransTableWid *mTransTableWid;
};

#endif // Z_STATUSWID_H
