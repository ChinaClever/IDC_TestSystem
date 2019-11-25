#ifndef MV1_LOGALARMWID_H
#define MV1_LOGALARMWID_H

#include "logcom/logcomwid.h"

class MV1_LogAlarmWid : public LogComWid
{
    Q_OBJECT
public:
    explicit MV1_LogAlarmWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // MV1_LOGALARMWID_H
