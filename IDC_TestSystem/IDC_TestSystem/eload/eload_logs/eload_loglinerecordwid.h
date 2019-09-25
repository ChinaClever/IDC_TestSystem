#ifndef ELOAD_LOGLINERECORDWID_H
#define ELOAD_LOGLINERECORDWID_H

#include "ELoad_logenvwid.h"

class ELoad_LogLineRecordWid : public LogComWid
{
    Q_OBJECT
public:
    explicit ELoad_LogLineRecordWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // ELOAD_LOGLINERECORDWID_H
