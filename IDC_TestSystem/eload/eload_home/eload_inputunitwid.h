#ifndef ELOAD_INPUTUNITWID_H
#define ELOAD_INPUTUNITWID_H

#include "eload_rtu/eload_rtusent.h"
#include "eload_com/in_datapackets.h"

namespace Ui {
class ELoad_InputUnitWid;
}

class ELoad_InputUnitWid : public QWidget
{
    Q_OBJECT

public:
    explicit ELoad_InputUnitWid(QWidget *parent = 0);
    ~ELoad_InputUnitWid();

    void init(int addr, int bit);

protected:
    void updateWid();

private slots:
    void initFunSLot();
    void timeoutDone();
    void on_openBtn_clicked();
    void on_closeBtn_clicked();
    void on_checkBox_clicked(bool checked);
    void on_horizontalScrollBar_valueChanged(int value);

private:
    Ui::ELoad_InputUnitWid *ui;

    QTimer *timer;
    sObjData *mObjData;
    ELoad_RtuSent *mRtu;
    int mAddr, mBit;
};

#endif // ELOAD_INPUTUNITWID_H
