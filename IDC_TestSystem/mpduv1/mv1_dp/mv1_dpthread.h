#ifndef MV1_DPTHREAD_H
#define MV1_DPTHREAD_H

#include "mv1_dpsavetrans.h"
#include "dpcom/dpthread.h"
#include "mv1_sql/mv1_dbmodbuscmd.h"
#include "mv1_com/mv1_datapackets.h"

class MV1_DpThread : public DpThread
{
    Q_OBJECT
    explicit MV1_DpThread(QObject *parent = nullptr);
public:
    static MV1_DpThread *bulid(QObject *parent = nullptr);
    ~MV1_DpThread();

protected:
     void insertItem(DbModbusCmdItem &item){MV1_DbModbusCmd::bulid()->insertItem(item);}
     int getTimeOut() {return MV1_ConfigFile::bulid()->item->logMins;}
     bool getStart();
};

#endif // MV1_DPTHREAD_H
