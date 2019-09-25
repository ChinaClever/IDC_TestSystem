#ifndef SI_ADDRSETWID_H
#define SI_ADDRSETWID_H

#include <QWidget>
#include "si_com/sidatapackets.h"

namespace Ui {
class SI_AddrSetWid;
}

class SI_AddrSetWid : public QWidget
{
    Q_OBJECT

public:
    explicit SI_AddrSetWid(QWidget *parent = 0);
    ~SI_AddrSetWid();

    void initPkt(SI_Rtu_Recv *pkt) {m_pkt = pkt;}
signals:
    void updateSig(int);

protected:
    void updateData(SI_Rtu_Recv *pkt);

private slots:
    void initFunSLot();
    void on_sureBtn_clicked();

    void on_editBtn_clicked();

private:
    Ui::SI_AddrSetWid *ui;
    SI_Rtu_Recv *m_pkt;
};

#endif // SI_ADDRSETWID_H
