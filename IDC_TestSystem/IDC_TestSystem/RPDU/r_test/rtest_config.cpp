/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "rtest_config.h"

RTest_Config::RTest_Config()
{
    item->isSnmp = true;
    item->serialNum.name = "RPDU";
}


RTest_Config *RTest_Config::bulid()
{
    static RTest_Config* sington = nullptr;
    if(sington == nullptr)
        sington = new RTest_Config();
    return sington;
}
