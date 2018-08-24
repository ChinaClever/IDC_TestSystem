#ifndef Z_LOGMODBUSTRANSWID_H
#define Z_LOGMODBUSTRANSWID_H
#include "z_logmodbuscmdwid.h"

class Z_LogModbusTransWid: public LogComWid
{
    Q_OBJECT
public:
    explicit Z_LogModbusTransWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // Z_LOGMODBUSTRANSWID_H
