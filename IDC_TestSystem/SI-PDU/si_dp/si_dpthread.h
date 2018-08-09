#ifndef SI_DPTHREAD_H
#define SI_DPTHREAD_H

#include "si_dpsavetrans.h"
#include "dpcom/dpthread.h"
#include "si_sql/sidbmodbuscmd.h"

class SI_DpThread : public DpThread
{
    Q_OBJECT
public:
    explicit SI_DpThread(QObject *parent = nullptr);
    ~SI_DpThread();

protected:
     void insertItem(DbModbusCmdItem &item){SiDbModbusCmd::bulid()->insertItem(item);}
     int getTimeOut() {return SiConfigFile::bulid()->item->logMins;}
     bool getStart();
};

#endif // SI_DPTHREAD_H
