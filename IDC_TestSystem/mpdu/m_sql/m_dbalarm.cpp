#include "m_dbalarm.h"

M_DbAlarm::M_DbAlarm()
{
    createTable();
}

M_DbAlarm *M_DbAlarm::bulid()
{
   static M_DbAlarm* sington = nullptr;
   if(sington == nullptr)
       sington = new M_DbAlarm();
   return sington;
}

