#ifndef RSET_SNMPTHREAD_H
#define RSET_SNMPTHREAD_H

#include "r_snmp/r_snmptrans.h"


class RSet_SnmpThread : public QThread
{
    Q_OBJECT
public:
    explicit RSet_SnmpThread(QObject *parent = nullptr);
    ~RSet_SnmpThread();

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
    R_SnmpTrans *mSnmp;

    QList<sSnmpSetCmd> mList;
};

#endif // RSET_SNMPTHREAD_H
