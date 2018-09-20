#ifndef ZTEST_LINEITEMWID_H
#define ZTEST_LINEITEMWID_H

#include <QWidget>
#include "../z_testthreshold/ztest_thresholdoutputwid.h"
namespace Ui {
class ZTest_LineItemWid;
}

class ZTest_LineItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZTest_LineItemWid(QWidget *parent = 0);
    ~ZTest_LineItemWid();

    void initwid(int mode, int type);

    int mReg;
    ZTest_ThresholdItemWid *mWid[3];

protected:
    QString getTypeName(int type);
    int getReg(int mode, int type);
private:
    Ui::ZTest_LineItemWid *ui;
};

#endif // ZTEST_LINEITEMWID_H
