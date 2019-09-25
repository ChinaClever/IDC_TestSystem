#ifndef BUSLOGMODBUSTRANSWID_H
#define BUSLOGMODBUSTRANSWID_H

#include "buslogmodbuscmdwid.h"

class BusLogModbusTransWid : public LogComWid
{
    Q_OBJECT
public:
    explicit BusLogModbusTransWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // BUSLOGMODBUSTRANSWID_H
