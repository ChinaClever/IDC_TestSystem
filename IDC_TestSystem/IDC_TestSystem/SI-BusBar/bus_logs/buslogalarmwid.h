#ifndef BUSLOGALARMWID_H
#define BUSLOGALARMWID_H

#include "logcom/logcomwid.h"
#include "bus_sql/busdbalarm.h"

class BusLogAlarmWid : public LogComWid
{
    Q_OBJECT
public:
    explicit BusLogAlarmWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // BUSLOGALARMWID_H
