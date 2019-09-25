#include "eload_dbenv.h"

ELoad_DbEnv::ELoad_DbEnv()
{
    createTable();
}

ELoad_DbEnv *ELoad_DbEnv::bulid()
{
    static ELoad_DbEnv* sington = nullptr;
    if(sington == nullptr)
        sington = new ELoad_DbEnv();
    return sington;
}

