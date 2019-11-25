#ifndef MV1_LOGENVWID_H
#define MV1_LOGENVWID_H

#include "mv1_logalarmwid.h"

class MV1_LogEnvWid : public LogComWid
{
    Q_OBJECT
public:
    explicit MV1_LogEnvWid(QWidget *parent = nullptr);


protected:
    void initTable();
    BasicSql *getDb();
};

#endif // MV1_LOGENVWID_H
