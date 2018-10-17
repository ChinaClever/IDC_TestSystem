#include "mtest_config.h"

MTest_Config::MTest_Config()
{
    item->isSnmp = true;
    item->serialNum.name = "M-PDU";
}


MTest_Config *MTest_Config::bulid()
{
    static MTest_Config* sington = nullptr;
    if(sington == nullptr)
        sington = new MTest_Config();
    return sington;
}
