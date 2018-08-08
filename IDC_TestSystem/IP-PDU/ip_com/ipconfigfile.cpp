/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ipconfigfile.h"

IP_ConfigFile::IP_ConfigFile()
{
    item = new IpConfigItem();
    item->cmdModel = 1;
    item->msecs = 10;
}

IP_ConfigFile *IP_ConfigFile::bulid()
{
    static IP_ConfigFile* sington = nullptr;
    if(sington == nullptr)
        sington = new IP_ConfigFile();
    return sington;
}


int IP_ConfigFile::getVersion()
{
    QString prefix = getPrefix();
    QString str = QString("%1_version_num").arg(prefix);
    int ret = sys_configFile_readInt(str, prefix);
    if(ret <= 0)  ret = 0;
    return ret;
}

/**
 * @brief 设置相数
 * @param num
 */
void IP_ConfigFile::setVersion(int num)
{
    QString prefix = getPrefix();
    QString str = QString("%1_version_num").arg(prefix);
    sys_configFile_writeParam(str, QString::number(num), prefix);
}
