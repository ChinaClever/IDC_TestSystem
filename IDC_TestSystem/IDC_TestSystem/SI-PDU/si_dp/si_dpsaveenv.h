#ifndef SI_DPSAVEENV_H
#define SI_DPSAVEENV_H

#include "si_dpsavethreshold.h"
#include "dpcom/dpsaveenv.h"
#include "si_sql/sidbenv.h"

class SI_DpSaveEnv : public DpSaveEnv
{
    Q_OBJECT
public:
    explicit SI_DpSaveEnv(QObject *parent = nullptr);

protected:
    void insertItem(DbEnvItem &item){SiDbEnv::bulid()->insertItem(item);}
};

#endif // SI_DPSAVEENV_H
