#ifndef ZSET_OUTPUTELEWID_H
#define ZSET_OUTPUTELEWID_H

#include <QWidget>
#include "zset_eleitemwid.h"
#include "z_setting/z_setrtu/zset_rtuthread.h"
#include "z_setting/z_setsnmp/zset_snmpthread.h"
namespace Ui {
class ZSet_OutputEleWid;
}

class ZSet_OutputEleWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZSet_OutputEleWid(QWidget *parent = 0);
    ~ZSet_OutputEleWid();

protected:
    void initwid();

protected slots:
    void updateTextSlot(QString str);

private slots:
    void on_checkBox_clicked(bool checked);
    void on_pushButton_clicked();
    void on_cleanRadio_clicked(bool checked);

private:
    Ui::ZSet_OutputEleWid *ui;
    ZSet_RtuThread *mRtu;
    ZSet_SnmpThread *mSnmp;
    ZSet_EleItemWid *mWid[24];
    int mReg;
    void sendSnmp(int i);
    void sendRtu(int i);
};

#endif // ZSET_OUTPUTELEWID_H
