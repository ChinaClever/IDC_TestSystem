#ifndef Z_LOGALARMWID_H
#define Z_LOGALARMWID_H

#include "logcom/logcomwid.h"

class Z_LogAlarmWid : public LogComWid
{
    Q_OBJECT
public:
    explicit Z_LogAlarmWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // Z_LOGALARMWID_H
