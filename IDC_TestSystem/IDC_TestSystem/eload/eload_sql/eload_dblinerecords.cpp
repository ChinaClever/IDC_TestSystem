#include "eload_dblinerecords.h"

ELoad_DbLineRecords::ELoad_DbLineRecords()
{
    createTable();
}

ELoad_DbLineRecords *ELoad_DbLineRecords::bulid()
{
    static ELoad_DbLineRecords* sington = nullptr;
    if(sington == nullptr)
        sington = new ELoad_DbLineRecords();
    return sington;
}
