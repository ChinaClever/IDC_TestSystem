#ifndef MV1_LOGMODBUSTRANSWID_H
#define MV1_LOGMODBUSTRANSWID_H
#include "mv1_logmodbuscmdwid.h"

class MV1_LogModbusTransWid: public LogComWid
{
    Q_OBJECT
public:
    explicit MV1_LogModbusTransWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // MV1_LOGMODBUSTRANSWID_H
