#ifndef MV1SET_LINEITEMWID_H
#define MV1SET_LINEITEMWID_H

#include "../mv1_setthreshold/mv1set_thresholdoutputwid.h"

namespace Ui {
class MV1Set_LineItemWid;
}

class MV1Set_LineItemWid : public QWidget
{
    Q_OBJECT

public:
    explicit MV1Set_LineItemWid(QWidget *parent = 0);
    ~MV1Set_LineItemWid();

    void initwid(int mode, int type);

    int mReg;
    MV1Set_ThresholdItemWid *mWid[3];

protected:
    QString getTypeName(int type);
    int getReg(int mode, int type);

private:
    Ui::MV1Set_LineItemWid *ui;
};

#endif // MV1SET_LINEITEMWID_H
