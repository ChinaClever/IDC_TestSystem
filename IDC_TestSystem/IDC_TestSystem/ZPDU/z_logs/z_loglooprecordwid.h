#ifndef Z_LOGLOOPRECORDWID_H
#define Z_LOGLOOPRECORDWID_H

#include "z_logoutputrecordwid.h"

class Z_LogLoopRecordWid : public LogComWid
{
    Q_OBJECT
public:
    explicit Z_LogLoopRecordWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // Z_LOGLOOPRECORDWID_H
