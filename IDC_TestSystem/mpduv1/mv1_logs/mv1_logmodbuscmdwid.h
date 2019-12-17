#ifndef MV1_LOGMODBUSCMDWID_H
#define MV1_LOGMODBUSCMDWID_H

#include "mv1_logenvwid.h"

class MV1_LogModbusCmdWid : public LogComWid
{
    Q_OBJECT
public:
    explicit MV1_LogModbusCmdWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // MV1_LOGMODBUSCMDWID_H
