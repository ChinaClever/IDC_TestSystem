#ifndef ZSET_THRESHOLDOUTPUTWID_H
#define ZSET_THRESHOLDOUTPUTWID_H

#include <QWidget>
#include "zset_thresholditemwid.h"
namespace Ui {
class ZSet_ThresholdOutputWid;
}

class ZSet_ThresholdOutputWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZSet_ThresholdOutputWid(QWidget *parent = 0);
    ~ZSet_ThresholdOutputWid();
    void initwid(int mode);

protected:
    int getReg(int mode);
    QString getOid(int mode);

    void sendRtu(int i);
    void sendSnmp(int i);

protected slots:
   void updateTextSlot(QString str);

private slots:
    void on_checkBox_clicked(bool checked);
    void on_pushButton_clicked();
    void on_curSpinBox_valueChanged(int arg1);

private:
    Ui::ZSet_ThresholdOutputWid *ui;
    ZSet_RtuThread *mRtu;
    ZSet_SnmpThread *mSnmp;
    int mReg;
    QString mOid;

    ZSet_ThresholdItemWid *mWid[24];
};

#endif // ZSET_THRESHOLDOUTPUTWID_H
