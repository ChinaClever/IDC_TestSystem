#ifndef DPSLAVEENV_H
#define DPSLAVEENV_H

#include "dpsaverecord.h"

class DpSaveEnv : public DpSaveRecord
{
    Q_OBJECT
public:
    explicit DpSaveEnv(QObject *parent = nullptr);

protected:
    void saveLogItem(int id);
    virtual void insertItem(DbEnvItem &item)=0;
};

#endif // DPSLAVEENV_H
