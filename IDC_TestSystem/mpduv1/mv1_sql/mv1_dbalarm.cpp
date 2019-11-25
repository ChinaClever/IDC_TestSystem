/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1_dbalarm.h"

MV1_DbAlarm::MV1_DbAlarm()
{
    createTable();
}

MV1_DbAlarm *MV1_DbAlarm::bulid()
{
   static MV1_DbAlarm* sington = nullptr;
   if(sington == nullptr)
       sington = new MV1_DbAlarm();
   return sington;
}

