/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ipconfigfile.h"

IP_ConfigFile::IP_ConfigFile()
{

}

IP_ConfigFile *IP_ConfigFile::bulid()
{
    static IP_ConfigFile* sington = nullptr;
    if(sington == nullptr)
        sington = new IP_ConfigFile();
    return sington;
}


