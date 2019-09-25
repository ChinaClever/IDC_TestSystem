#ifndef RSET_OUTPUTELEWID_H
#define RSET_OUTPUTELEWID_H

#include <QWidget>
#include "rset_eleitemwid.h"
#include "r_setting/r_setrtu/rset_rtuthread.h"
#include "r_setting/r_setsnmp/rset_snmpthread.h"
namespace Ui {
class RSet_OutputEleWid;
}

class RSet_OutputEleWid : public QWidget
{
    Q_OBJECT

public:
    explicit RSet_OutputEleWid(QWidget *parent = 0);
    ~RSet_OutputEleWid();

protected:
    void initwid();

protected slots:
    void updateTextSlot(QString str);

private slots:
    void on_checkBox_clicked(bool checked);
    void on_pushButton_clicked();
    void on_cleanRadio_clicked(bool checked);

private:
    Ui::RSet_OutputEleWid *ui;
    RSet_RtuThread *mRtu;
    RSet_SnmpThread *mSnmp;
    RSet_EleItemWid *mWid[24];
    int mReg;
    void sendSnmp(int i);
    void sendRtu(int i);
};

#endif // RSET_OUTPUTELEWID_H
