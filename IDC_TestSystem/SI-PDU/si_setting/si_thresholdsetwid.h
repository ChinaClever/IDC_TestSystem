#ifndef SI_THRESHOLDSETWID_H
#define SI_THRESHOLDSETWID_H

#include "si_unitsetwid.h"

namespace Ui {
class SI_ThresholdSetWid;
}

enum {
    SI_SetMode_Vol,
    SI_SetMode_Cur,
    SI_SetMode_Tem,
    SI_SetMode_Hum,
};

class SI_ThresholdSetWid : public QWidget
{
    Q_OBJECT

public:
    explicit SI_ThresholdSetWid(QWidget *parent = 0);
    ~SI_ThresholdSetWid();

    void init(int mode, SI_RtuRecvLine &data);
signals:
    void updateSig(int addr);

protected:
    void initWid();
    QString getStr(int mode);
    double getRate(int mode);
    int getReg(int mode);
    int getLine(int mode, SI_RtuRecvLine &data);
    SI_sDataUnit *getUnit(int mode, SI_RtuRecvLine &data);

private:
    Ui::SI_ThresholdSetWid *ui;

    SI_UnitSetWid *mUnitSetWid[3];
};

#endif // SI_THRESHOLDSETWID_H
