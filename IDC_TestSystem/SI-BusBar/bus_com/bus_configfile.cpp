#include "bus_configfile.h"

BUS_ConfigFile::BUS_ConfigFile()
{
    item = new BusConfigItem();    
    item->cmdModel = 1;
    item->msecs = 10;
}

BUS_ConfigFile *BUS_ConfigFile::bulid()
{
    static BUS_ConfigFile* sington = nullptr;
    if(sington == nullptr)
        sington = new BUS_ConfigFile();
    return sington;
}
