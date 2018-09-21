#ifndef MSET_SWWID_H
#define MSET_SWWID_H

#include "mset_switemwid.h"

namespace Ui {
class MSet_SwWid;
}

class MSet_SwWid : public QWidget
{
    Q_OBJECT

public:
    explicit MSet_SwWid(QWidget *parent = 0);
    ~MSet_SwWid();

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
    Ui::MSet_SwWid *ui;

    MSet_SnmpThread *mSnmp;
    MSet_RtuThread *mRtu;
    MSet_SwItemWid *mWid[24];
    int mReg;
};

#endif // MSET_SWWID_H
