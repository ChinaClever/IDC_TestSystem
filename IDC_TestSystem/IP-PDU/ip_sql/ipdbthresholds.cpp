/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ipdbthresholds.h"

IpDbThresholds::IpDbThresholds()
{
    createTable();
}


IpDbThresholds *IpDbThresholds::bulid()
{
    static IpDbThresholds* sington = nullptr;
    if(sington == nullptr)
        sington = new IpDbThresholds();
    return sington;
}

