#ifndef Z_DPTHREAD_H
#define Z_DPTHREAD_H
#include "z_dpsavetrans.h"
#include "dpcom/dpthread.h"
#include "z_sql/z_dbmodbuscmd.h"
#include "z_com/z_datapackets.h"

class Z_DpThread : public DpThread
{
    Q_OBJECT
public:
    explicit Z_DpThread(QObject *parent = nullptr);
    ~Z_DpThread();

protected:
     void insertItem(DbModbusCmdItem &item){Z_DbModbusCmd::bulid()->insertItem(item);}
     int getTimeOut() {return Z_ConfigFile::bulid()->item->logMins;}
     bool getStart();
};


#endif // Z_DPTHREAD_H
