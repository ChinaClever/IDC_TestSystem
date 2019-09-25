#ifndef SILOGMODBUSTRANSWID_H
#define SILOGMODBUSTRANSWID_H

#include "silogmodbuscmdwid.h"

class SiLogModbusTransWid : public LogComWid
{
    Q_OBJECT
public:
    explicit SiLogModbusTransWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // SILOGMODBUSTRANSWID_H
