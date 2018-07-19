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
