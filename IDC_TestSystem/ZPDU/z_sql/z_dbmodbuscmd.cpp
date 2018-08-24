#include "z_dbmodbuscmd.h"

Z_DbModbusCmd::Z_DbModbusCmd()
{
    createTable();
}

Z_DbModbusCmd *Z_DbModbusCmd::bulid()
{
    static Z_DbModbusCmd* sington = nullptr;
    if(sington == nullptr)
        sington = new Z_DbModbusCmd();
    return sington;
}

