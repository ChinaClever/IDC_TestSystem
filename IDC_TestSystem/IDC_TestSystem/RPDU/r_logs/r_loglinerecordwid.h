#ifndef R_LOGLINERECORDWID_H
#define R_LOGLINERECORDWID_H

#include "r_logenvwid.h"

class R_LogLineRecordWid : public LogComWid
{
    Q_OBJECT
public:
    explicit R_LogLineRecordWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // R_LOGLINERECORDWID_H
