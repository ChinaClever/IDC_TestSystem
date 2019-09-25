#ifndef M_STATUSWID_H
#define M_STATUSWID_H

#include "m_com/m_datapackets.h"
#include "tablewid/linethresholdtablewid.h"
#include "tablewid/envtablewid.h"
#include "tablewid/transtablewid.h"
#include "tablewid/outputthresholdtablewid.h"


namespace Ui {
class M_StatusWid;
}

class M_StatusWid : public QWidget
{
    Q_OBJECT

public:
    explicit M_StatusWid(QWidget *parent = 0);
    ~M_StatusWid();

public slots:
    void simulateSlot(int);

protected slots:
     void initFunSLot();

private:
    Ui::M_StatusWid *ui;

    LineTableWid *mDevTableWid;
    EnvTableWid *mEnvTableWid;
    OutputTableWid *mOutputTableWid;
    OutputThresholdTableWid *mOutputThresholdTableWid;
    LineThresholdTableWid *mThresholdTableWid;
    TransTableWid *mTransTableWid;
};

#endif // M_STATUSWID_H
