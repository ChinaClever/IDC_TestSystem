/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "sidbalarm.h"

SiDbAlarm::SiDbAlarm()
{
    createTable();
}


SiDbAlarm *SiDbAlarm::bulid()
{
    static SiDbAlarm* sington = nullptr;
    if(sington == nullptr)
        sington = new SiDbAlarm();
    return sington;
}
