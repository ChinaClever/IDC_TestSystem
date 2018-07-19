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
