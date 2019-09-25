/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "r_configfile.h"

R_ConfigFile::R_ConfigFile()
{

}

R_ConfigFile *R_ConfigFile::bulid()
{
    static R_ConfigFile* sington = nullptr;
    if(sington == nullptr)
        sington = new R_ConfigFile();
    return sington;
}
