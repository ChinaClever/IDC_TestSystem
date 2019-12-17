#ifndef MV1SET_THRESHOLDOUTPUTWID_H
#define MV1SET_THRESHOLDOUTPUTWID_H

#include "mv1set_thresholditemwid.h"

namespace Ui {
class MV1Set_ThresholdOutputWid;
}

class MV1Set_ThresholdOutputWid : public QWidget
{
    Q_OBJECT

public:
    explicit MV1Set_ThresholdOutputWid(QWidget *parent = 0);
    ~MV1Set_ThresholdOutputWid();

    void initwid(int mode);

protected:
    int getReg(int mode);
    QString getOid(int mode);
    void sendSnmp(int i);
    void sendRtu(int i);

protected slots:
   void updateTextSlot(QString str);

private slots:
    void on_checkBox_clicked(bool checked);
    void on_pushButton_clicked();
    void on_curSpinBox_valueChanged(int arg1);

private:
    Ui::MV1Set_ThresholdOutputWid *ui;
    MV1Set_RtuThread *mRtu;
    MV1Set_SnmpThread *mSnmp;
    int mReg;
    QString mOid;

    MV1Set_ThresholdItemWid *mWid[24];
};

#endif // MV1SET_THRESHOLDOUTPUTWID_H
