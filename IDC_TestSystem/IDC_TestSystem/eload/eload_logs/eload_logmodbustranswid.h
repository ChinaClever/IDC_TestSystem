#ifndef ELOAD_LOGMODBUSTRANSWID_H
#define ELOAD_LOGMODBUSTRANSWID_H
#include "ELoad_logmodbuscmdwid.h"

class ELoad_LogModbusTransWid: public LogComWid
{
    Q_OBJECT
public:
    explicit ELoad_LogModbusTransWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // ELOAD_LOGMODBUSTRANSWID_H
