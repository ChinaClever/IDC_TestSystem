#ifndef M_LOGMODBUSCMDWID_H
#define M_LOGMODBUSCMDWID_H

#include "m_logenvwid.h"

class M_LogModbusCmdWid : public LogComWid
{
    Q_OBJECT
public:
    explicit M_LogModbusCmdWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // M_LOGMODBUSCMDWID_H
