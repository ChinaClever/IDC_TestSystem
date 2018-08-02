#ifndef IP_DPTHREAD_H
#define IP_DPTHREAD_H

#include "ip_dpalarmslave.h"
#include "dpcom/dpthread.h"
#include "ip_sql/ipdbmodbuscmd.h"

class IP_DpThread : public DpThread
{
    Q_OBJECT
public:
    explicit IP_DpThread(QObject *parent = nullptr);

protected:
     void insertItem(DbModbusCmdItem &item){IpDbModbusCmd::bulid()->insertItem(item);}
     int getTimeOut() {return IP_ConfigFile::bulid()->item->logMins;}
     bool getStart();
};

#endif // IP_DPTHREAD_H
