#include "eload_dbalarm.h"

ELoad_DbAlarm::ELoad_DbAlarm()
{
    createTable();
}

ELoad_DbAlarm *ELoad_DbAlarm::bulid()
{
   static ELoad_DbAlarm* sington = nullptr;
   if(sington == nullptr)
       sington = new ELoad_DbAlarm();
   return sington;
}
