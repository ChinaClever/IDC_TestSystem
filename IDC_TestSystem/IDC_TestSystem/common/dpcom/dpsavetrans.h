#ifndef DPSLAVETRANS_H
#define DPSLAVETRANS_H

#include "dpsaverecord.h"

class DpSaveTrans : public DpSaveRecord
{
    Q_OBJECT
public:
    explicit DpSaveTrans(QObject *parent = nullptr);

protected:
    void saveLogItem(int id);
    virtual void insertItem(DbModbusTransItem &item)=0;
};

#endif // DPSLAVETRANS_H
