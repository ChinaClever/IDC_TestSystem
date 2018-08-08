#ifndef DPSLAVELINE_H
#define DPSLAVELINE_H

#include "dpsaverecord.h"

class DpSaveLine : public DpSaveRecord
{
    Q_OBJECT
public:
    explicit DpSaveLine(QObject *parent = nullptr);

protected:
    virtual void saveLogItem(int id);
    virtual void insertItem(DbLineRecordItem &item)=0;
};

#endif // DPSLAVELINE_H
