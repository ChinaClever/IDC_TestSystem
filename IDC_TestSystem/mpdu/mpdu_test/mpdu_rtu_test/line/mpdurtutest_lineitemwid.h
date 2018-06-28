#ifndef MPDURTUTEST_LINEITEMWID_H
#define MPDURTUTEST_LINEITEMWID_H

#include "../threshold/mpdurtutest_thresholditemwid.h"

namespace Ui {
class MpduRtuTest_LineItemWid;
}

class MpduRtuTest_LineItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit MpduRtuTest_LineItemWid(QWidget *parent = 0);
    ~MpduRtuTest_LineItemWid();

    void initwid(int mode, int type);

    int mReg;
    MpduRtuTest_ThresholdItemWid *mWid[3];

protected:
    QString getTypeName(int type);
    int getReg(int mode, int type);

private:
    Ui::MpduRtuTest_LineItemWid *ui;
};

#endif // MPDURTUTEST_LINEITEMWID_H
