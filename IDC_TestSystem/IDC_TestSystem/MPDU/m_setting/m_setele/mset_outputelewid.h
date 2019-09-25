#ifndef MSET_OUTPUTELEWID_H
#define MSET_OUTPUTELEWID_H

#include "mset_eleitemwid.h"

namespace Ui {
class MSet_OutputEleWid;
}

class MSet_OutputEleWid : public QWidget
{
    Q_OBJECT

public:
    explicit MSet_OutputEleWid(QWidget *parent = 0);
    ~MSet_OutputEleWid();

protected:
    void initwid();

protected slots:
    void updateTextSlot(QString str);

private slots:
    void on_checkBox_clicked(bool checked);
    void on_pushButton_clicked();
    void on_cleanRadio_clicked(bool checked);

private:
    Ui::MSet_OutputEleWid *ui;
    MSet_RtuThread *mRtu;
    MSet_SnmpThread* mSnmp;
    MSet_EleItemWid *mWid[24];
    int mReg;
    void sendSnmp(int i);
    void sendRtu(int i);
};

#endif // MSET_OUTPUTELEWID_H
