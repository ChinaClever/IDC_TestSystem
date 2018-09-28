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
//    void sendRtu(int i);
//    void sendSnmp(int i);

protected slots:
   void updateTextSlot(QString str);
   void update();
private slots:
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
    int caseCount;//snmp情况计数
    int cycleCount;//循环计数
    QList<int> select;
    QTimer* timer;
    void produceCmd(QList<int> & select , int& mtimers);//产生命令函数
    QString getOid(int i);//获取Oid节点
    void snmpFirstCase(int& mtimers);//snmp的第一种情况
    void snmpOtherCase(QList<int> & select , int& mtimers , bool end);//snmp的其他情况
    void sendSnmp(QList<int>& select , int& mtimers);

    void rtuFirstCase(int& mtimers);//rtu的第一种情况
    void rtuOtherCase(QList<int> & select , int& mtimers , bool end);//rtu的其他情况
    void sendRtu(QList<int>& select , int& mtimers);
};

#endif // ZSET_SWCYCLEWID_H
