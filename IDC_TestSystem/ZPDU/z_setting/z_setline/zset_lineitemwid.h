#ifndef ZSET_LINEITEMWID_H
#define ZSET_LINEITEMWID_H

#include <QWidget>
#include "../z_testthreshold/ztest_thresholdoutputwid.h"
namespace Ui {
class ZSet_LineItemWid;
}

class ZSet_LineItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZSet_LineItemWid(QWidget *parent = 0);
    ~ZSet_LineItemWid();

    void initwid(int mode, int type);

    int mReg;
    ZTest_ThresholdItemWid *mWid[3];

protected:
    QString getTypeName(int type);
    int getReg(int mode, int type);
private:
    Ui::ZSet_LineItemWid *ui;
};

#endif // ZSET_LINEITEMWID_H
