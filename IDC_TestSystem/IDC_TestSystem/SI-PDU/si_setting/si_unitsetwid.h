#ifndef SI_UNITSETWID_H
#define SI_UNITSETWID_H

#include "si_addrsetwid.h"

namespace Ui {
class SI_UnitSetWid;
}

class SI_UnitSetWid : public QWidget
{
    Q_OBJECT

public:
    explicit SI_UnitSetWid(QWidget *parent = 0);
    ~SI_UnitSetWid();

    void init(SI_sDataUnit *unit, int line, double rate, const QString &str, int reg);

protected:
    void updateData(int line);
    void setData(int addr, int reg, int value);

public slots:
    void updateSlot(int addr);

private slots:
    void on_maxBtn_clicked();
    void on_minBtn_clicked();

private:
    Ui::SI_UnitSetWid *ui;
    int mAddr, mLine, mReg; double mRate;
    SI_sDataUnit *mUnit;
};

#endif // SI_UNITSETWID_H
