#include "eload_dbmodbuscmd.h"

ELoad_DbModbusCmd::ELoad_DbModbusCmd()
{
    createTable();
}

ELoad_DbModbusCmd *ELoad_DbModbusCmd::bulid()
{
    static ELoad_DbModbusCmd* sington = nullptr;
    if(sington == nullptr)
        sington = new ELoad_DbModbusCmd();
    return sington;
}

