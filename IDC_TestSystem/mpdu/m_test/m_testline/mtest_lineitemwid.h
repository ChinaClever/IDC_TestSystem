#ifndef MTEST_LINEITEMWID_H
#define MTEST_LINEITEMWID_H

#include "../m_testthreshold/mtest_thresholdoutputwid.h"

namespace Ui {
class MTest_LineItemWid;
}

class MTest_LineItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit MTest_LineItemWid(QWidget *parent = 0);
    ~MTest_LineItemWid();

    void initwid(int mode, int type);

    int mReg;
    MTest_ThresholdItemWid *mWid[3];

protected:
    QString getTypeName(int type);
    int getReg(int mode, int type);

private:
    Ui::MTest_LineItemWid *ui;
};

#endif // MTEST_LINEITEMWID_H
