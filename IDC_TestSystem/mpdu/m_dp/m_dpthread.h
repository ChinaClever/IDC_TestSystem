#ifndef M_DPTHREAD_H
#define M_DPTHREAD_H

#include "m_dpslavetrans.h"
#include "dpcom/dpthread.h"
#include "m_sql/m_dbmodbuscmd.h"
#include "m_com/m_datapackets.h"

class M_DpThread : public DpThread
{
    Q_OBJECT
public:
    explicit M_DpThread(QObject *parent = nullptr);

protected:
     void insertItem(DbModbusCmdItem &item){M_DbModbusCmd::bulid()->insertItem(item);}
     int getTimeOut() {return M_ConfigFile::bulid()->item->logMins;}
     bool getStart();
};

#endif // M_DPTHREAD_H
