/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ipdbenv.h"

IpDbEnv::IpDbEnv()
{
   createTable();
}

IpDbEnv *IpDbEnv::bulid()
{
    static IpDbEnv* sington = nullptr;
    if(sington == nullptr)
        sington = new IpDbEnv();
    return sington;
}
