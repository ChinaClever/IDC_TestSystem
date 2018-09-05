#ifndef BUSTEST_MAINWID_H
#define BUSTEST_MAINWID_H

#include <QWidget>
#include "bustest_envsetwid.h"
#include "bustest_thresholdsetwid.h"
namespace Ui {
class BUSTest_MainWid;
}

class BUSTest_MainWid : public QWidget
{
    Q_OBJECT

public:
    explicit BUSTest_MainWid(QWidget *parent = 0);
    ~BUSTest_MainWid();
private slots:
    void updateAddrSlot(int mAddr);
    void updateBusSlot(int mBus);


private:
    Ui::BUSTest_MainWid *ui;
    BUSTEST_EnvSetWid* mEnvSetWid;
    BUSTEST_ThresholdSetWid* mThresholdSetWid;
};

#endif // BUSTEST_MAINWID_H
