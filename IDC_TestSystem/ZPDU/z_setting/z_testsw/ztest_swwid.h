#ifndef ZTEST_SWWID_H
#define ZTEST_SWWID_H

#include "ztest_switemwid.h"

namespace Ui {
class ZTest_SwWid;
}

class ZTest_SwWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZTest_SwWid(QWidget *parent = 0);
    ~ZTest_SwWid();

protected:
    void initwid();
    void sendRtu(int i);
    void sendSnmp(int i);

protected slots:
   void updateTextSlot(QString str);

private slots:
   void on_checkBox_clicked(bool checked);
   void on_openRadio_clicked(bool checked);
   void on_closeRadio_clicked(bool checked);
   void on_pushButton_clicked();

private:
    Ui::ZTest_SwWid *ui;

    ZSet_SnmpThread *mSnmp;
    ZSet_RtuThread *mRtu;
    ZTest_SwItemWid *mWid[24];
    int mReg;
};

#endif // ZTEST_SWWID_H
