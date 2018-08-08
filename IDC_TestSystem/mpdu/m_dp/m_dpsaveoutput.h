#ifndef M_DPSAVEOUTPUT_H
#define M_DPSAVEOUTPUT_H
#include "m_dpsavelinethreshold.h"
#include "dpcom/dpsaveoutput.h"
#include "m_sql/m_dboutputrecords.h"

class M_DpSaveOutput : public DpSaveOutput
{
    Q_OBJECT
public:
    explicit M_DpSaveOutput(QObject *parent = nullptr);

protected:
    void insertItem(DbOutputItem &item){M_DbOutputRecords::bulid()->insertItem(item);}
};

#endif // M_DPSAVEOUTPUT_H
