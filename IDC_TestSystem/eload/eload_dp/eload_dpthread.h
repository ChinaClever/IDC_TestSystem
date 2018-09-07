#ifndef ELOAD_DPTHREAD_H
#define ELOAD_DPTHREAD_H
#include "ELoad_dpsavetrans.h"
#include "dpcom/dpthread.h"
#include "ELoad_sql/ELoad_dbmodbuscmd.h"
#include "ELoad_com/in_datapackets.h"

class ELoad_DpThread : public DpThread
{
    Q_OBJECT
public:
    explicit ELoad_DpThread(QObject *parent = nullptr);
    ~ELoad_DpThread();

protected:
     void insertItem(DbModbusCmdItem &item){ELoad_DbModbusCmd::bulid()->insertItem(item);}
     int getTimeOut() {return ELoad_ConfigFile::bulid()->item->logMins;}
     bool getStart();
};

#endif // ELOAD_DPTHREAD_H
