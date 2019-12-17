#include "mv1test_config.h"

MV1Test_Config::MV1Test_Config()
{
    item->isSnmp = true;
    item->serialNum.name = "MPDUV1";
}


MV1Test_Config *MV1Test_Config::bulid()
{
    static MV1Test_Config* sington = nullptr;
    if(sington == nullptr)
        sington = new MV1Test_Config();
    return sington;
}
