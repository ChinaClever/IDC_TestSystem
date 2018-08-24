#ifndef DPSAVELOOP_H
#define DPSAVELOOP_H

#include "dpsaveoutput.h"
#include "sqlcom/dblooprecords.h"

class DpSaveLoop : public DpSaveOutput
{
    Q_OBJECT
public:
    explicit DpSaveLoop(QObject *parent = nullptr);

protected:
    virtual void saveLogItem(int id);
    virtual void insertItem(DbLoopItem &item)=0;
};

#endif // DPSAVELOOP_H
