#ifndef M_LOGOUTPUTRECORDWID_H
#define M_LOGOUTPUTRECORDWID_H

#include "m_loglinethresholdwid.h"

class M_LogOutputRecordWid : public LogComWid
{
    Q_OBJECT
public:
    explicit M_LogOutputRecordWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // M_LOGOUTPUTRECORDWID_H
