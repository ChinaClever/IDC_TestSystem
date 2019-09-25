#ifndef M_LOGENVWID_H
#define M_LOGENVWID_H

#include "m_logalarmwid.h"

class M_LogEnvWid : public LogComWid
{
    Q_OBJECT
public:
    explicit M_LogEnvWid(QWidget *parent = nullptr);


protected:
    void initTable();
    BasicSql *getDb();
};

#endif // M_LOGENVWID_H
