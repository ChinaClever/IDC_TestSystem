#ifndef ZTEST_SNMPTHREAD_H
#define ZTEST_SNMPTHREAD_H

#include "z_snmp/z_snmptrans.h"


class ZTest_SnmpThread : public QThread
{
    Q_OBJECT
public:
    explicit ZTest_SnmpThread(QObject *parent = nullptr);
    ~ZTest_SnmpThread();

    void setCmd(const sSnmpSetCmd &cmd);

protected:
    int sentSetCmd(const sSnmpSetCmd &cmd);
    void run();

signals:
    void cmdSig(QString);

public slots:

private:
    bool isRun;
    QMutex *mMutex;
    Z_SnmpTrans *mSnmp;

    QList<sSnmpSetCmd> mList;
};

#endif // ZTEST_SNMPTHREAD_H
