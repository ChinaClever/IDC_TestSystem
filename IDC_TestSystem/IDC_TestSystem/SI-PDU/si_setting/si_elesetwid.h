#ifndef SI_ELESETWID_H
#define SI_ELESETWID_H

#include "si_thresholdsetwid.h"

namespace Ui {
class SI_EleSetWid;
}

class SI_EleSetWid : public QWidget
{
    Q_OBJECT

public:
    explicit SI_EleSetWid(QWidget *parent = 0);
    ~SI_EleSetWid();

    void updateData(int addr, int line, uint *array, int br);

private slots:
    void on_cleverBtn_clicked();

    void on_editBtn_clicked();

private:
    Ui::SI_EleSetWid *ui;
    int mAddr;
};

#endif // SI_ELESETWID_H
