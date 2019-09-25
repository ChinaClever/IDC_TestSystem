#ifndef ELOAD_LOGALARMWID_H
#define ELOAD_LOGALARMWID_H

#include "logcom/logcomwid.h"

class ELoad_LogAlarmWid : public LogComWid
{
    Q_OBJECT
public:
    explicit ELoad_LogAlarmWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // ELOAD_LOGALARMWID_H
