#ifndef IP_DPSLAVERECORD_H
#define IP_DPSLAVERECORD_H

#include "ip_com/ipdatapackets.h"
#include "dpcom/dpsaveline.h"
#include "ip_sql/ipdbrealrecords.h"

class IP_DpSaveRecord : public DpSaveLine
{
    Q_OBJECT
public:
    explicit IP_DpSaveRecord(QObject *parent = nullptr);

protected:
    void insertItem(DbLineRecordItem &item){IpDbRealRecords::bulid()->insertItem(item);}
};

#endif // IP_DPSLAVERECORD_H
