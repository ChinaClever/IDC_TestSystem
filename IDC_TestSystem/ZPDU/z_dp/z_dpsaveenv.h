#ifndef Z_DPSAVEENV_H
#define Z_DPSAVEENV_H
#include "z_dpalarmsave.h"
#include "z_sql/z_dbenv.h"
#include "dpcom/dpsaveenv.h"

class Z_DpSaveEnv : public DpSaveEnv
{
    Q_OBJECT
public:
    explicit Z_DpSaveEnv(QObject *parent = nullptr);

protected:
    void insertItem(DbEnvItem &item){Z_DbEnv::bulid()->insertItem(item);}
};

#endif // Z_DPSAVEENV_H
