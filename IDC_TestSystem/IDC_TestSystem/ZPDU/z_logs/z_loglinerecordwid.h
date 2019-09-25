#ifndef Z_LOGLINERECORDWID_H
#define Z_LOGLINERECORDWID_H

#include "z_logenvwid.h"

class Z_LogLineRecordWid : public LogComWid
{
    Q_OBJECT
public:
    explicit Z_LogLineRecordWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // Z_LOGLINERECORDWID_H
