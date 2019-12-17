#ifndef MV1SET_SNMPTHREAD_H
#define MV1SET_SNMPTHREAD_H

#include "mv1_snmp/mv1_snmptrans.h"

class MV1Set_SnmpThread : public QThread
{
    Q_OBJECT
public:
    explicit MV1Set_SnmpThread(QObject *parent = nullptr);
    ~MV1Set_SnmpThread();

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
    MV1_SnmpTrans *mSnmp;

    QList<sSnmpSetCmd> mList;
};

#endif // MV1SET_SNMPTHREAD_H
