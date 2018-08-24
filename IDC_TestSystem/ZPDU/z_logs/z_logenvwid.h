#ifndef Z_LOGENVWID_H
#define Z_LOGENVWID_H

#include "z_logalarmwid.h"

class Z_LogEnvWid : public LogComWid
{
    Q_OBJECT
public:
    explicit Z_LogEnvWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // Z_LOGENVWID_H
