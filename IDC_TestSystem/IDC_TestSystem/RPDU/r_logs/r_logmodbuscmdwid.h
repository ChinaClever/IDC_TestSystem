#ifndef R_LOGMODBUSCMDWID_H
#define R_LOGMODBUSCMDWID_H

#include "r_loglinethresholdwid.h"

class R_LogModbusCmdWid : public LogComWid
{
    Q_OBJECT
public:
    explicit R_LogModbusCmdWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // R_LOGMODBUSCMDWID_H
