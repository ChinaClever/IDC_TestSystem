#include "ztest_config.h"

ZTest_Config::ZTest_Config()
{

}


ZTest_Config *ZTest_Config::bulid()
{
    static ZTest_Config* sington = nullptr;
    if(sington == nullptr)
        sington = new ZTest_Config();
    return sington;
}
