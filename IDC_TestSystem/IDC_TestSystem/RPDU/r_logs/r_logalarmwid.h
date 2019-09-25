#ifndef R_LOGALARMWID_H
#define R_LOGALARMWID_H

#include "logcom/logcomwid.h"

class R_LogAlarmWid : public LogComWid
{
    Q_OBJECT
public:
    explicit R_LogAlarmWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // R_LOGALARMWID_H
