#ifndef R_DPSAVEOUTPUT_H
#define R_DPSAVEOUTPUT_H
#include "r_dpsavelinethreshold.h"
#include "dpcom/dpsaveoutput.h"
#include "r_sql/r_dboutputrecords.h"

class R_DpSaveOutput : public DpSaveOutput
{
    Q_OBJECT
public:
    explicit R_DpSaveOutput(QObject *parent = nullptr);

protected:
    void insertItem(DbOutputItem &item){R_DbOutputRecords::bulid()->insertItem(item);}
};

#endif // R_DPSAVEOUTPUT_H
