#ifndef ELOAD_LOGENVWID_H
#define ELOAD_LOGENVWID_H

#include "eload_logalarmwid.h"

class ELoad_LogEnvWid : public LogComWid
{
    Q_OBJECT
public:
    explicit ELoad_LogEnvWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // ELOAD_LOGENVWID_H
