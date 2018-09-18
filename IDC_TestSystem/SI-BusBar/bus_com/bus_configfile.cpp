/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "bus_configfile.h"

BUS_ConfigFile::BUS_ConfigFile()
{

}

BUS_ConfigFile *BUS_ConfigFile::bulid()
{
    static BUS_ConfigFile* sington = nullptr;
    if(sington == nullptr)
        sington = new BUS_ConfigFile();
    return sington;
}
