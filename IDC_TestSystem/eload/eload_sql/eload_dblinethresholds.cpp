#include "eload_dblinethresholds.h"

ELoad_DbLineThresholds::ELoad_DbLineThresholds()
{
    createTable();
}


ELoad_DbLineThresholds *ELoad_DbLineThresholds::bulid()
{
    static ELoad_DbLineThresholds* sington = nullptr;
    if(sington == nullptr)
        sington = new ELoad_DbLineThresholds();
    return sington;
}
