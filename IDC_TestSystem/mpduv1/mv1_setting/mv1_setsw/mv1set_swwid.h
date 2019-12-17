#ifndef MV1SET_SWWID_H
#define MV1SET_SWWID_H

#include "mv1set_switemwid.h"

namespace Ui {
class MV1Set_SwWid;
}

class MV1Set_SwWid : public QWidget
{
    Q_OBJECT

public:
    explicit MV1Set_SwWid(QWidget *parent = 0);
    ~MV1Set_SwWid();

protected:
    void initwid();
    void sendRtu(int i);
    void sendSnmp(int i);

protected slots:
   void updateTextSlot(QString str);

private slots:
    void on_checkBox_clicked(bool checked);
    void on_pushButton_clicked();
    void on_openRadio_clicked(bool checked);
    void on_closeRadio_clicked(bool checked);

private:
    Ui::MV1Set_SwWid *ui;

    MV1Set_SnmpThread *mSnmp;
    MV1Set_RtuThread *mRtu;
    MV1Set_SwItemWid *mWid[24];
    int mReg;
};

#endif // MV1SET_SWWID_H
