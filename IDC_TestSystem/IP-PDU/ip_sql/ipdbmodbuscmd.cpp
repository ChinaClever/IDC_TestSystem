#include "ipdbmodbuscmd.h"

IpDbModbusCmd::IpDbModbusCmd()
{
   createTable();
}

IpDbModbusCmd *IpDbModbusCmd::bulid()
{
    static IpDbModbusCmd* sington = nullptr;
    if(sington == nullptr)
        sington = new IpDbModbusCmd();
    return sington;
}
