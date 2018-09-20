#ifndef ZSET_SNMPTHREAD_H
#define ZSET_SNMPTHREAD_H

#include "z_snmp/z_snmptrans.h"


class ZSet_SnmpThread : public QThread
{
    Q_OBJECT
public:
    explicit ZSet_SnmpThread(QObject *parent = nullptr);
    ~ZSet_SnmpThread();

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

#endif // ZSET_SNMPTHREAD_H
