#include "eload_dbmodbustrans.h"

ELoad_DbModbusTrans::ELoad_DbModbusTrans()
{
    createTable();
}

ELoad_DbModbusTrans *ELoad_DbModbusTrans::bulid()
{
    static ELoad_DbModbusTrans* sington = nullptr;
    if(sington == nullptr)
        sington = new ELoad_DbModbusTrans();
    return sington;
}
