/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ipdbalarm.h"

IpDbAlarm::IpDbAlarm()
{
     createTable();
}

IpDbAlarm *IpDbAlarm::bulid()
{
    static IpDbAlarm* sington = nullptr;
    if(sington == nullptr)
        sington = new IpDbAlarm();
    return sington;
}
