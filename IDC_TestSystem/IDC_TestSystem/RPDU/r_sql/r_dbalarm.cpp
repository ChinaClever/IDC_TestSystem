/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "r_dbalarm.h"

R_DbAlarm::R_DbAlarm()
{
    createTable();
}

R_DbAlarm *R_DbAlarm::bulid()
{
   static R_DbAlarm* sington = nullptr;
   if(sington == nullptr)
       sington = new R_DbAlarm();
   return sington;
}
