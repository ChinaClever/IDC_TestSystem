#ifndef ZTEST_ENVITEMWID_H
#define ZTEST_ENVITEMWID_H

#include <QWidget>
#include "../z_testthreshold/ztest_thresholditemwid.h"
namespace Ui {
class ZTest_EnvItemWid;
}

class ZTest_EnvItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZTest_EnvItemWid(QWidget *parent = 0);
    ~ZTest_EnvItemWid();

    void initwid(int mode, int type);

    int mReg;
    ZTest_ThresholdItemWid *mWid[3];

protected:
    QString getTypeName(int type);
    int getReg(int mode, int type);

private:
    Ui::ZTest_EnvItemWid *ui;
};

#endif // ZTEST_ENVITEMWID_H
