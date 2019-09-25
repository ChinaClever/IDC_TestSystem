#ifndef ZSET_SWWID_H
#define ZSET_SWWID_H

#include "zset_switemwid.h"

namespace Ui {
class ZSet_SwWid;
}

class ZSet_SwWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZSet_SwWid(QWidget *parent = 0);
    ~ZSet_SwWid();

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
    Ui::ZSet_SwWid *ui;

    ZSet_SnmpThread *mSnmp;
    ZSet_RtuThread *mRtu;
    ZSet_SwItemWid *mWid[24];
    int mReg;
};

#endif // ZSET_SWWID_H
