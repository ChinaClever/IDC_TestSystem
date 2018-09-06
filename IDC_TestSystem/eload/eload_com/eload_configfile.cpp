#include "eload_configfile.h"

ELoad_ConfigFile::ELoad_ConfigFile()
{
    item = new sELoad_ConfigItem();
    item->cmdModel = 1;
    item->msecs = 10;
}

ELoad_ConfigFile *ELoad_ConfigFile::bulid()
{
    static ELoad_ConfigFile* sington = nullptr;
    if(sington == nullptr)
        sington = new ELoad_ConfigFile();
    return sington;
}

