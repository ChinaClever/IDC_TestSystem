#ifndef M_DPSLAVEENV_H
#define M_DPSLAVEENV_H
#include "m_dpsaveoutput.h"
#include "m_sql/m_dbenv.h"
#include "dpcom/dpsaveenv.h"

class M_DpSlaveEnv : public DpSaveEnv
{
    Q_OBJECT
public:
    explicit M_DpSlaveEnv(QObject *parent = nullptr);

protected:
    void insertItem(DbEnvItem &item){M_DbEnv::bulid()->insertItem(item);}
};

#endif // M_DPSLAVEENV_H
