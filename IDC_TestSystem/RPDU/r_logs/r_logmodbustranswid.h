#ifndef R_LOGMODBUSTRANSWID_H
#define R_LOGMODBUSTRANSWID_H
#include "r_logmodbuscmdwid.h"

class R_LogModbusTransWid: public LogComWid
{
    Q_OBJECT
public:
    explicit R_LogModbusTransWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // R_LOGMODBUSTRANSWID_H
