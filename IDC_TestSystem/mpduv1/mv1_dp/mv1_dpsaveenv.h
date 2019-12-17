#ifndef MV1_DPSLAVEENV_H
#define MV1_DPSLAVEENV_H
#include "mv1_dpsaveoutput.h"
#include "mv1_sql/mv1_dbenv.h"
#include "dpcom/dpsaveenv.h"

class MV1_DpSaveEnv : public DpSaveEnv
{
    Q_OBJECT
public:
    explicit MV1_DpSaveEnv(QObject *parent = nullptr);

protected:
    void insertItem(DbEnvItem &item){MV1_DbEnv::bulid()->insertItem(item);}
};

#endif // MV1_DPSLAVEENV_H
