#ifndef M_LOGMODBUSTRANSWID_H
#define M_LOGMODBUSTRANSWID_H
#include "m_logmodbuscmdwid.h"

class M_LogModbusTransWid: public LogComWid
{
    Q_OBJECT
public:
    explicit M_LogModbusTransWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // M_LOGMODBUSTRANSWID_H
