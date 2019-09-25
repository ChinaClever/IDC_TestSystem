#ifndef Z_DPSAVELOOP_H
#define Z_DPSAVELOOP_H
#include "z_dpsaveoutput.h"
#include "dpcom/dpsaveloop.h"
#include "z_sql/z_dblooprecords.h"

class Z_DpSaveLoop : public DpSaveLoop
{
    Q_OBJECT
public:
    explicit Z_DpSaveLoop(QObject *parent = nullptr);

protected:
    void insertItem(DbLoopItem &item){Z_DbLoopRecords::bulid()->insertItem(item);}
};

#endif // Z_DPSAVELOOP_H
