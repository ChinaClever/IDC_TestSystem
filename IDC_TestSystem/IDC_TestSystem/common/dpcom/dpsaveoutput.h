#ifndef DPSAVEOUTPUT_H
#define DPSAVEOUTPUT_H

#include "dpsaverecord.h"
#include "sqlcom/dboutputrecords.h"

class DpSaveOutput : public DpSaveRecord
{
    Q_OBJECT
public:
    explicit DpSaveOutput(QObject *parent = nullptr);

protected:
    virtual void saveLogItem(int id);
    virtual void insertItem(DbOutputItem &item)=0;
};

#endif // DPSAVEOUTPUT_H
