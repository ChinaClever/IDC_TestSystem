#include "m_dblinerecords.h"

M_DbLineRecords::M_DbLineRecords()
{
    createTable();
}

M_DbLineRecords *M_DbLineRecords::bulid()
{
    static M_DbLineRecords* sington = nullptr;
    if(sington == nullptr)
        sington = new M_DbLineRecords();
    return sington;
}
