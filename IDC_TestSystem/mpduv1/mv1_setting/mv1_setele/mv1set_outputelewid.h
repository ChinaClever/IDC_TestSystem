#ifndef MV1SET_OUTPUTELEWID_H
#define MV1SET_OUTPUTELEWID_H

#include "mv1set_eleitemwid.h"

namespace Ui {
class MV1Set_OutputEleWid;
}

class MV1Set_OutputEleWid : public QWidget
{
    Q_OBJECT

public:
    explicit MV1Set_OutputEleWid(QWidget *parent = 0);
    ~MV1Set_OutputEleWid();

protected:
    void initwid();

protected slots:
    void updateTextSlot(QString str);

private slots:
    void on_checkBox_clicked(bool checked);
    void on_pushButton_clicked();
    void on_cleanRadio_clicked(bool checked);

private:
    Ui::MV1Set_OutputEleWid *ui;
    MV1Set_RtuThread *mRtu;
    MV1Set_SnmpThread* mSnmp;
    MV1Set_EleItemWid *mWid[24];
    int mReg;
    void sendSnmp(int i);
    void sendRtu(int i);
};

#endif // MV1SET_OUTPUTELEWID_H
