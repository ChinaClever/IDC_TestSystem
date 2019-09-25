#ifndef IPLOGALARMWID_H
#define IPLOGALARMWID_H

#include "logcom/logcomwid.h"

class IpLogAlarmWid : public LogComWid
{
    Q_OBJECT
public:
    explicit IpLogAlarmWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // IPLOGALARMWID_H
