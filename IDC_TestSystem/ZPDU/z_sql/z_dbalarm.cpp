#include "z_dbalarm.h"

Z_DbAlarm::Z_DbAlarm()
{
    createTable();
}

Z_DbAlarm *Z_DbAlarm::bulid()
{
   static Z_DbAlarm* sington = nullptr;
   if(sington == nullptr)
       sington = new Z_DbAlarm();
   return sington;
}
