#ifndef R_LOGLOOPRECORDWID_H
#define R_LOGLOOPRECORDWID_H

#include "r_logoutputrecordwid.h"

class R_LogLoopRecordWid : public LogComWid
{
    Q_OBJECT
public:
    explicit R_LogLoopRecordWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // R_LOGLOOPRECORDWID_H
