#ifndef MSET_SWCYCLEWID_H
#define MSET_SWCYCLEWID_H

#include <QWidget>
#include "mset_swcycleitemwid.h"
namespace Ui {
class MSet_SwCycleWid;
}

class MSet_SwCycleWid : public QWidget
{
    Q_OBJECT

public:
    explicit MSet_SwCycleWid(QWidget *parent = 0);
    ~MSet_SwCycleWid();

protected:
    void initwid();

private:
    void produceCmd(int& mtimers);//产生命令函数
    QString getOid(int i);//获取Oid节点
    void snmpFirstCase(int& mtimers);//snmp的第一种情况
    void snmpOtherCase(int& mtimers , bool end);//snmp的其他情况
    void sendSnmp(int& mtimers);
    void rtuFirstCase(int& mtimers);//rtu的第一种情况
    void rtuOtherCase(int& mtimers , bool end);//rtu的其他情况
    void sendRtu(int& mtimers);
    void updateCycleCount();//更新循环次数

protected slots:
   void updateTextSlot(QString str);
   void updateSlot();
   void on_checkBox_clicked(bool checked);
   void on_radioButton_clicked(bool checked);
   void on_startBtn_clicked();
   void on_stopBtn_clicked();

private:
    Ui::MSet_SwCycleWid *ui;
    MSet_SnmpThread *mSnmp;
    MSet_RtuThread *mRtu;
    MSet_SwCycleItemWid *mWid[24];
    int mReg;
    int mCaseCount;//snmp情况计数
    int mCycleCount;//循环计数
    QList<int> mSelect;
    QTimer* mTimer;
};

#endif // MSET_SWCYCLEWID_H
