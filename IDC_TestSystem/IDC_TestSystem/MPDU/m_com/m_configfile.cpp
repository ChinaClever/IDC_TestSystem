/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "m_configfile.h"

M_ConfigFile::M_ConfigFile()
{
}

M_ConfigFile *M_ConfigFile::bulid()
{
    static M_ConfigFile* sington = nullptr;
    if(sington == nullptr)
        sington = new M_ConfigFile();
    return sington;
}

