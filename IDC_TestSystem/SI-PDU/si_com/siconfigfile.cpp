#include "siconfigfile.h"

SiConfigFile::SiConfigFile()
{
     item = new SiConfigItem();
}

SiConfigFile *SiConfigFile::bulid()
{
    static SiConfigFile* sington = nullptr;
    if(sington == nullptr)
        sington = new SiConfigFile();
    return sington;
}
