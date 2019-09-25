#ifndef RSET_SWCYCLEWID_H
#define RSET_SWCYCLEWID_H

#include <QWidget>
#include "rset_swcycleitemwid.h"
namespace Ui {
class RSet_SwCycleWid;
}

class RSet_SwCycleWid : public QWidget
{
    Q_OBJECT

public:
    explicit RSet_SwCycleWid(QWidget *parent = 0);
    ~RSet_SwCycleWid();

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
    Ui::RSet_SwCycleWid *ui;
    RSet_SnmpThread *mSnmp;
    RSet_RtuThread *mRtu;
    RSet_SwCycleItemWid *mWid[24];
    int mReg;
    int mCaseCount;//情况计数
    int mCycleCount;//循环计数
    bool mStartOrStop;//开始停止标志
    QList<int> mSelect;
    QTimer* mTimer;
    bool mDelayCloseSwFlag;//延长发送关继电器控制标志 配合mCaseCount一起控制
    //mCaseCount==0&&false：继续 mCaseCount==1&&false：停止 mCaseCount==1&&true:继续
};

#endif // RSET_SWCYCLEWID_H
