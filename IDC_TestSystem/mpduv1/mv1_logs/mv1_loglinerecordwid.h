#ifndef MV1_LOGLINERECORDWID_H
#define MV1_LOGLINERECORDWID_H

#include "mv1_logmodbustranswid.h"

class MV1_LogLineRecordWid : public LogComWid
{
    Q_OBJECT
public:
    explicit MV1_LogLineRecordWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // MV1_LOGLINERECORDWID_H
