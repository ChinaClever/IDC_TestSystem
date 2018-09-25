#ifndef MSET_THRESHOLDOUTPUTWID_H
#define MSET_THRESHOLDOUTPUTWID_H

#include "mset_thresholditemwid.h"

namespace Ui {
class MSet_ThresholdOutputWid;
}

class MSet_ThresholdOutputWid : public QWidget
{
    Q_OBJECT

public:
    explicit MSet_ThresholdOutputWid(QWidget *parent = 0);
    ~MSet_ThresholdOutputWid();

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
    Ui::MSet_ThresholdOutputWid *ui;
    MSet_RtuThread *mRtu;
    MSet_SnmpThread *mSnmp;
    int mReg;
    QString mOid;

    MSet_ThresholdItemWid *mWid[24];
};

#endif // MSET_THRESHOLDOUTPUTWID_H
