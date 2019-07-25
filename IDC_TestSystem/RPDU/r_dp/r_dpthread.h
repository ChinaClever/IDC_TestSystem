#ifndef R_DPTHREAD_H
#define R_DPTHREAD_H
#include "r_dpsavetrans.h"
#include "dpcom/dpthread.h"
#include "r_sql/r_dbmodbuscmd.h"
#include "r_com/r_datapackets.h"

class R_DpThread : public DpThread
{
    Q_OBJECT
    explicit R_DpThread(QObject *parent = nullptr);
public:
    static R_DpThread *bulid(QObject *parent = nullptr);
    ~R_DpThread();

protected:
     void insertItem(DbModbusCmdItem &item){R_DbModbusCmd::bulid()->insertItem(item);}
     int getTimeOut() {return R_ConfigFile::bulid()->item->logMins;}
     bool getStart();
};


#endif // Z_DPTHREAD_H
