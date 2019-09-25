#ifndef R_LOGOUTPUTRECORDWID_H
#define R_LOGOUTPUTRECORDWID_H

#include "r_logmodbustranswid.h"

class R_LogOutputRecordWid : public LogComWid
{
    Q_OBJECT
public:
    explicit R_LogOutputRecordWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // R_LOGOUTPUTRECORDWID_H
