/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "eload_configfile.h"

ELoad_ConfigFile::ELoad_ConfigFile()
{
}

ELoad_ConfigFile *ELoad_ConfigFile::bulid()
{
    static ELoad_ConfigFile* sington = nullptr;
    if(sington == nullptr)
        sington = new ELoad_ConfigFile();
    return sington;
}

