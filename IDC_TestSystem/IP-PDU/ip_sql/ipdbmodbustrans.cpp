/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ipdbmodbustrans.h"

IpDbModbusTrans::IpDbModbusTrans()
{
  createTable();
}

IpDbModbusTrans *IpDbModbusTrans::bulid()
{
    static IpDbModbusTrans* sington = nullptr;
    if(sington == nullptr)
        sington = new IpDbModbusTrans();
    return sington;
}
