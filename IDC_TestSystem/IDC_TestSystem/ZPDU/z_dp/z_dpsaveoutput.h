#ifndef Z_DPSAVEOUTPUT_H
#define Z_DPSAVEOUTPUT_H
#include "z_dpsavelinethreshold.h"
#include "dpcom/dpsaveoutput.h"
#include "z_sql/z_dboutputrecords.h"

class Z_DpSaveOutput : public DpSaveOutput
{
    Q_OBJECT
public:
    explicit Z_DpSaveOutput(QObject *parent = nullptr);

protected:
    void insertItem(DbOutputItem &item){Z_DbOutputRecords::bulid()->insertItem(item);}
};

#endif // Z_DPSAVEOUTPUT_H
