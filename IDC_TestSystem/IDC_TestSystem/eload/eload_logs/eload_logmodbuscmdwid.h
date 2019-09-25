#ifndef ELOAD_LOGMODBUSCMDWID_H
#define ELOAD_LOGMODBUSCMDWID_H
#include "ELoad_loglinethresholdwid.h"

class ELoad_LogModbusCmdWid : public LogComWid
{
    Q_OBJECT
public:
    explicit ELoad_LogModbusCmdWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // ELOAD_LOGMODBUSCMDWID_H
