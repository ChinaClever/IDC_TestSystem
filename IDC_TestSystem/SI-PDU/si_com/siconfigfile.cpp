/*
 * Si 配置信息的静态类
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "siconfigfile.h"

SiConfigFile::SiConfigFile()
{

}

SiConfigFile *SiConfigFile::bulid()
{
    static SiConfigFile* sington = nullptr;
    if(sington == nullptr)
        sington = new SiConfigFile();
    return sington;
}
