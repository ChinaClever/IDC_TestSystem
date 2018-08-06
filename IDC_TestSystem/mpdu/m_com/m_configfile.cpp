#include "m_configfile.h"

M_ConfigFile::M_ConfigFile()
{
    item = new sM_ConfigItem();
    item->cmdModel = 1;
    item->msecs = 10;
    item->outputNum = 24;
}

M_ConfigFile *M_ConfigFile::bulid()
{
    static M_ConfigFile* sington = nullptr;
    if(sington == nullptr)
        sington = new M_ConfigFile();
    return sington;
}

