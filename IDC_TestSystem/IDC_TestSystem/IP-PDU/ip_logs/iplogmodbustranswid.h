#ifndef IPLOGMODBUSTRANSWID_H
#define IPLOGMODBUSTRANSWID_H

#include "iplogmodbuscmdwid.h"

class IpLogModbusTransWid : public LogComWid
{
    Q_OBJECT
public:
    explicit IpLogModbusTransWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // IPLOGMODBUSTRANSWID_H
