#ifndef RSET_THRESHOLDOUTPUTWID_H
#define RSET_THRESHOLDOUTPUTWID_H

#include <QWidget>
#include "rset_thresholditemwid.h"
namespace Ui {
class RSet_ThresholdOutputWid;
}

class RSet_ThresholdOutputWid : public QWidget
{
    Q_OBJECT

public:
    explicit RSet_ThresholdOutputWid(QWidget *parent = 0);
    ~RSet_ThresholdOutputWid();
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
    Ui::RSet_ThresholdOutputWid *ui;
    RSet_RtuThread *mRtu;
    RSet_SnmpThread *mSnmp;
    int mReg;
    QString mOid;

    RSet_ThresholdItemWid *mWid[24];
};

#endif // RSET_THRESHOLDOUTPUTWID_H
