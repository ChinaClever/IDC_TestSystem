#ifndef R_DPSAVEENV_H
#define R_DPSAVEENV_H
#include "r_dpalarmsave.h"
#include "r_sql/r_dbenv.h"
#include "dpcom/dpsaveenv.h"

class R_DpSaveEnv : public DpSaveEnv
{
    Q_OBJECT
public:
    explicit R_DpSaveEnv(QObject *parent = nullptr);

protected:
    void insertItem(DbEnvItem &item){R_DbEnv::bulid()->insertItem(item);}
};

#endif // Z_DPSAVEENV_H
