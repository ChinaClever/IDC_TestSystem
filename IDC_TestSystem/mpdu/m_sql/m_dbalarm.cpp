/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
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

