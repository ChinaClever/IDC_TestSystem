#ifndef Z_LOGOUTPUTRECORDWID_H
#define Z_LOGOUTPUTRECORDWID_H

#include "z_logmodbustranswid.h"

class Z_LogOutputRecordWid : public LogComWid
{
    Q_OBJECT
public:
    explicit Z_LogOutputRecordWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // Z_LOGOUTPUTRECORDWID_H
