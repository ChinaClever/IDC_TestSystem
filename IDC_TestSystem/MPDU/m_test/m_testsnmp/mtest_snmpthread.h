#ifndef MTEST_SNMPTHREAD_H
#define MTEST_SNMPTHREAD_H

#include "m_snmp/m_snmptrans.h"

class MTest_SnmpThread : public QThread
{
    Q_OBJECT
public:
    explicit MTest_SnmpThread(QObject *parent = nullptr);
    ~MTest_SnmpThread();

    void setCmd(const sSnmpSetCmd &cmd) {mList.append(cmd);}

protected:
    int sentSetCmd(const sSnmpSetCmd &cmd);
    void run();

signals:
    void cmdSig(QString);

public slots:

private:
    bool isRun;
    QMutex *mMutex;
    M_SnmpTrans *mSnmp;

    QList<sSnmpSetCmd> mList;
};

#endif // MTEST_SNMPTHREAD_H
