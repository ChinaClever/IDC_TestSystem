#ifndef RSET_SWWID_H
#define RSET_SWWID_H

#include "rset_switemwid.h"

namespace Ui {
class RSet_SwWid;
}

class RSet_SwWid : public QWidget
{
    Q_OBJECT

public:
    explicit RSet_SwWid(QWidget *parent = 0);
    ~RSet_SwWid();

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
    Ui::RSet_SwWid *ui;

    RSet_SnmpThread *mSnmp;
    RSet_RtuThread *mRtu;
    RSet_SwItemWid *mWid[24];
    int mReg;
};

#endif // RSET_SWWID_H
