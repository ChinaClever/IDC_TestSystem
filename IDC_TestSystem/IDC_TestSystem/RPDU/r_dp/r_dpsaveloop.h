#ifndef R_DPSAVELOOP_H
#define R_DPSAVELOOP_H
#include "r_dpsaveoutput.h"
#include "dpcom/dpsaveloop.h"
#include "r_sql/r_dblooprecords.h"

class R_DpSaveLoop : public DpSaveLoop
{
    Q_OBJECT
public:
    explicit R_DpSaveLoop(QObject *parent = nullptr);

protected:
    void insertItem(DbLoopItem &item){R_DbLoopRecords::bulid()->insertItem(item);}
};

#endif // R_DPSAVELOOP_H
