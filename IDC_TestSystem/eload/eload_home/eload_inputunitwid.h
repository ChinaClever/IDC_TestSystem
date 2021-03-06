﻿#ifndef ELOAD_INPUTUNITWID_H
#define ELOAD_INPUTUNITWID_H

#include "eload_rtu/eload_rtusent.h"
#include "eload_com/in_datapackets.h"
#include "eload_rtu/in_rtutrans.h"
#include <QScrollBar>
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
    int getValue();
    void setValue(int value);
    void setResistance(int id , int value);

protected:
    void updateWid();
    void staticSetCurUpdate();
    void autoSetCurUpdate(int addr , int bit , QList<bool> flag);
    void setText(ushort value , ushort alarm,QString text,QLabel* lab,double rate);

private slots:
    void initFunSLot();
    void setFunSLot();
    void setResSLot();
    void timeoutDone();
    void on_openBtn_clicked();
    void on_closeBtn_clicked();
    void on_checkBox_clicked(bool checked);
    void on_horizontalScrollBar_sliderMoved(int position);

    void on_horizontalScrollBar_sliderReleased();

private:
    Ui::ELoad_InputUnitWid *ui;

    QTimer *timer;
    sObjData *mObjData;
    sRtuCount *mRtuCount;
    ELoad_RtuSent *mRtu;
    int mAddr, mBit ,mValue;
};
void setRes(int addr,int bit,int value,bool ret);
#endif // ELOAD_INPUTUNITWID_H
