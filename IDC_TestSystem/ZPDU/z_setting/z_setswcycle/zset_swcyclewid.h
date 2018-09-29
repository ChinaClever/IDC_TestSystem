#ifndef ZSET_SWCYCLEWID_H
#define ZSET_SWCYCLEWID_H

#include <QWidget>
#include "zset_swcycleitemwid.h"
namespace Ui {
class ZSet_SwCycleWid;
}

class ZSet_SwCycleWid : public QWidget
{
    Q_OBJECT

public:
    explicit ZSet_SwCycleWid(QWidget *parent = 0);
    ~ZSet_SwCycleWid();

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
    Ui::ZSet_SwCycleWid *ui;
    ZSet_SnmpThread *mSnmp;
    ZSet_RtuThread *mRtu;
    ZSet_SwCycleItemWid *mWid[24];
    int mReg;
    int mCaseCount;//情况计数
    int mCycleCount;//循环计数
    QList<int> mSelect;
    QTimer* mTimer;
};

#endif // ZSET_SWCYCLEWID_H
