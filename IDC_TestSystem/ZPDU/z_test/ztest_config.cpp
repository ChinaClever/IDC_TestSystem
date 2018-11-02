/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ztest_config.h"

ZTest_Config::ZTest_Config()
{
    item->isSnmp = true;
    item->serialNum.name = "ZPDU";
}


ZTest_Config *ZTest_Config::bulid()
{
    static ZTest_Config* sington = nullptr;
    if(sington == nullptr)
        sington = new ZTest_Config();
    return sington;
}
