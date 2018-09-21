#ifndef MSET_SNMPTHREAD_H
#define MSET_SNMPTHREAD_H

#include "m_snmp/m_snmptrans.h"

class MSet_SnmpThread : public QThread
{
    Q_OBJECT
public:
    explicit MSet_SnmpThread(QObject *parent = nullptr);
    ~MSet_SnmpThread();

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

#endif // MSET_SNMPTHREAD_H
