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
    void snmpAllOpenOrCloseCase(int& mtimers);//snmp全开全关
    void snmpOtherCase(int& mtimers , bool end);//snmp的其他情况
    void sendSnmp(int& mtimers);
    void rtuAllOpenOrCloseCase(int& mtimers);//rtu全开全关
    void rtuOtherCase(int& mtimers , bool end);//rtu的其他情况
    void sendRtu(int& mtimers);
    void updateCycleCount();//更新循环次数
    void startSend();
    void stopSend();

protected slots:
   void updateTextSlot(QString str);
   void updateSlot();
   void on_checkBox_clicked(bool checked);
   void on_radioButton_clicked(bool checked);
   void on_startBtn_clicked();

private:
    Ui::ZSet_SwCycleWid *ui;
    ZSet_SnmpThread *mSnmp;
    ZSet_RtuThread *mRtu;
    ZSet_SwCycleItemWid *mWid[24];
    int mReg;
    int mCaseCount;//情况计数
    int mCycleCount;//循环计数
    bool mStartOrStop;//开始停止标志
    QList<int> mSelect;
    QTimer* mTimer;
};

#endif // ZSET_SWCYCLEWID_H
