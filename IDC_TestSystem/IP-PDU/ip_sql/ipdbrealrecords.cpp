/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ipdbrealrecords.h"

IpDbRealRecords::IpDbRealRecords()
{
  createTable();
}

IpDbRealRecords *IpDbRealRecords::bulid()
{
    static IpDbRealRecords* sington = nullptr;
    if(sington == nullptr)
        sington = new IpDbRealRecords();
    return sington;
}
