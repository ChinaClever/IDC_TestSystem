#ifndef R_LOGENVWID_H
#define R_LOGENVWID_H

#include "r_logalarmwid.h"

class R_LogEnvWid : public LogComWid
{
    Q_OBJECT
public:
    explicit R_LogEnvWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // R_LOGENVWID_H
