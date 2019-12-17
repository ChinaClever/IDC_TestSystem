#ifndef MV1_DPSAVEOUTPUT_H
#define MV1_DPSAVEOUTPUT_H
#include "mv1_dpsavelinethreshold.h"
#include "dpcom/dpsaveoutput.h"
#include "mv1_sql/mv1_dboutputrecords.h"

class MV1_DpSaveOutput : public DpSaveOutput
{
    Q_OBJECT
public:
    explicit MV1_DpSaveOutput(QObject *parent = nullptr);

protected:
    void insertItem(DbOutputItem &item){MV1_DbOutputRecords::bulid()->insertItem(item);}
};

#endif // MV1_DPSAVEOUTPUT_H
