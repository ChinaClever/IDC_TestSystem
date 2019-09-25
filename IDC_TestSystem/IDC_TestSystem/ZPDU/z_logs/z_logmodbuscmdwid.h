#ifndef Z_LOGMODBUSCMDWID_H
#define Z_LOGMODBUSCMDWID_H

#include "z_loglinethresholdwid.h"

class Z_LogModbusCmdWid : public LogComWid
{
    Q_OBJECT
public:
    explicit Z_LogModbusCmdWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // Z_LOGMODBUSCMDWID_H
