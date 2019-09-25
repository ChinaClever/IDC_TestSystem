#ifndef ELOAD_DPSAVEENV_H
#define ELOAD_DPSAVEENV_H
#include "ELoad_dpalarmsave.h"
#include "ELoad_sql/ELoad_dbenv.h"
#include "dpcom/dpsaveenv.h"

class ELoad_DpSaveEnv : public DpSaveEnv
{
    Q_OBJECT
public:
    explicit ELoad_DpSaveEnv(QObject *parent = nullptr);

protected:
    void insertItem(DbEnvItem &item){ELoad_DbEnv::bulid()->insertItem(item);}
};

#endif // ELOAD_DPSAVEENV_H
