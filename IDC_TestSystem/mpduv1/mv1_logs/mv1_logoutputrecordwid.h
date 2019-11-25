#ifndef MV1_LOGOUTPUTRECORDWID_H
#define MV1_LOGOUTPUTRECORDWID_H

#include "mv1_loglinethresholdwid.h"

class MV1_LogOutputRecordWid : public LogComWid
{
    Q_OBJECT
public:
    explicit MV1_LogOutputRecordWid(QWidget *parent = nullptr);

protected:
    void initTable();
    BasicSql *getDb();
};

#endif // MV1_LOGOUTPUTRECORDWID_H
