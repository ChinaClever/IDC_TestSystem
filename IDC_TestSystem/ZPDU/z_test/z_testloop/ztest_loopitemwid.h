#ifndef ZTEST_LOOPITEMWID_H
#define ZTEST_LOOPITEMWID_H

#include <QWidget>
#include "../z_testthreshold/ztest_thresholdoutputwid.h"
namespace Ui {
class ZTest_LoopItemWid;
}

class ZTest_LoopItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZTest_LoopItemWid(QWidget *parent = 0);
    ~ZTest_LoopItemWid();

    void initwid(int type);

    int mReg;
    ZTest_ThresholdItemWid *mWid[6];

protected:
    QString getTypeName(int type);
    int getReg(int type);
private:
    Ui::ZTest_LoopItemWid *ui;
};

#endif // ZTEST_LOOPITEMWID_H
