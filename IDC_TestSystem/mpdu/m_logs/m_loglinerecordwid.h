#ifndef M_LOGLINERECORDWID_H
#define M_LOGLINERECORDWID_H

#include "m_logmodbustranswid.h"

class M_LogLineRecordWid : public LogComWid
{
    Q_OBJECT
public:
    explicit M_LogLineRecordWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // M_LOGLINERECORDWID_H
