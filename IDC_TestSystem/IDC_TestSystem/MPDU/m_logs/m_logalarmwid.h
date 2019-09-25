#ifndef M_LOGALARMWID_H
#define M_LOGALARMWID_H

#include "logcom/logcomwid.h"

class M_LogAlarmWid : public LogComWid
{
    Q_OBJECT
public:
    explicit M_LogAlarmWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // M_LOGALARMWID_H
