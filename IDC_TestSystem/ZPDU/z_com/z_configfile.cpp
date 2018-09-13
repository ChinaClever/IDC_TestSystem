/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "z_configfile.h"

Z_ConfigFile::Z_ConfigFile()
{

}

Z_ConfigFile *Z_ConfigFile::bulid()
{
    static Z_ConfigFile* sington = nullptr;
    if(sington == nullptr)
        sington = new Z_ConfigFile();
    return sington;
}
