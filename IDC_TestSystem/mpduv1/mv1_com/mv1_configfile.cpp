/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mv1_configfile.h"

MV1_ConfigFile::MV1_ConfigFile()
{
}

MV1_ConfigFile *MV1_ConfigFile::bulid()
{
    static MV1_ConfigFile* sington = nullptr;
    if(sington == nullptr)
        sington = new MV1_ConfigFile();
    return sington;
}

