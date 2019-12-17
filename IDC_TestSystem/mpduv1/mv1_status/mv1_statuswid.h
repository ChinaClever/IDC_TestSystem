#ifndef MV1_STATUSWID_H
#define MV1_STATUSWID_H

#include "mv1_com/mv1_datapackets.h"
#include "tablewid/linethresholdtablewid.h"
#include "tablewid/envtablewid.h"
#include "tablewid/transtablewid.h"
#include "tablewid/outputthresholdtablewid.h"


namespace Ui {
class MV1_StatusWid;
}

class MV1_StatusWid : public QWidget
{
    Q_OBJECT

public:
    explicit MV1_StatusWid(QWidget *parent = 0);
    ~MV1_StatusWid();

public slots:
    void simulateSlot(int);

protected slots:
     void initFunSLot();

private:
    Ui::MV1_StatusWid *ui;

    LineTableWid *mDevTableWid;
    EnvTableWid *mEnvTableWid;
    OutputTableWid *mOutputTableWid;
    OutputThresholdTableWid *mOutputThresholdTableWid;
    LineThresholdTableWid *mThresholdTableWid;
    TransTableWid *mTransTableWid;
};

#endif // MV1_STATUSWID_H
