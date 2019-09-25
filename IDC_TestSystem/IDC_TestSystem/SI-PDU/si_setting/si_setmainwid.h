#ifndef SI_SETMAINWID_H
#define SI_SETMAINWID_H

#include "si_elesetwid.h"


namespace Ui {
class SI_SetMainWid;
}

class SI_SetMainWid : public QWidget
{
    Q_OBJECT

public:
    explicit SI_SetMainWid(QWidget *parent = 0);
    ~SI_SetMainWid();

private slots:
    void initFunSLot();
    void updateSlot(int);

private:
    Ui::SI_SetMainWid *ui;

    SI_Rtu_Recv *mData;
    SI_AddrSetWid *mAddrSetWid;
    SI_EleSetWid *mEleSetWid;
    SI_ThresholdSetWid *mThresholdSetWid[4];
};

#endif // SI_SETMAINWID_H
