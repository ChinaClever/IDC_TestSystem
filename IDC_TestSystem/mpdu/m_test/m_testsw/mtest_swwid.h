#ifndef MTEST_SWWID_H
#define MTEST_SWWID_H

#include "mtest_switemwid.h"

namespace Ui {
class MTest_SwWid;
}

class MTest_SwWid : public QWidget
{
    Q_OBJECT

public:
    explicit MTest_SwWid(QWidget *parent = 0);
    ~MTest_SwWid();

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
    Ui::MTest_SwWid *ui;

    MTest_SnmpThread *mSnmp;
    MTest_RtuThread *mRtu;
    MTest_SwItemWid *mWid[24];
    int mReg;
};

#endif // MTEST_SWWID_H
