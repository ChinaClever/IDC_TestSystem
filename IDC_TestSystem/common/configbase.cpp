#include "configbase.h"

ConfigBase::ConfigBase()
{

}


/**
 * @brief 获取串口名称
 * @return 串口名
 */
QString ConfigBase::getSerialName()
{
    QString prefix = getPrefix();
    QString str = QString("%1_COM").arg(prefix);
    return sys_configFile_readStr(str, prefix);
}

/**
 * @brief 设置串口名
 * @param name
 */
void ConfigBase::setSerialName(const QString &name)
{
    QString prefix = getPrefix();
    QString str = QString("%1_COM").arg(prefix);
    sys_configFile_writeParam(str, name, prefix);
}

/**
 * @brief 获取相数
 * @return
 */
int ConfigBase::getLineNum()
{
    QString prefix = getPrefix();
    QString str = QString("%1_line_num").arg(prefix);
    int ret = sys_configFile_readInt(str, prefix);
    if(ret <= 0)  ret = 1;
    return ret;
}

/**
 * @brief 设置相数
 * @param num
 */
void ConfigBase::setLineNum(int num)
{
    QString prefix = getPrefix();
    QString str = QString("%1_line_num").arg(prefix);
    sys_configFile_writeParam(str, QString::number(num), prefix);
}


/**
 * @brief 获取级联数量
 * @return
 */
int ConfigBase::getDevNum()
{
    QString prefix = getPrefix();
    QString str = QString("%1_dev_num").arg(prefix);
    int ret = sys_configFile_readInt(str, prefix);
    if(ret <= 0)  ret = 1;

    return ret;
}

/**
 * @brief 设置级联数据
 * @param num
 */
void ConfigBase::setDevNum(int num)
{
    QString prefix = getPrefix();
    QString str = QString("%1_dev_num").arg(prefix);
    sys_configFile_writeParam(str, QString::number(num), prefix);
}

/**
 * @brief ConfigBase::getModbusCmd
 * @return
 */
int ConfigBase::getModbusCmd()
{
    QString prefix = getPrefix();
    QString str = QString("%1_modbus_cmd").arg(prefix);
    int ret = sys_configFile_readInt(str, prefix);
    if(ret <= 0)  ret = 1;
    return ret;
}

void ConfigBase::setModbusCmd(int num)
{
    QString prefix = getPrefix();
    QString str = QString("%1_modbus_cmd").arg(prefix);
    sys_configFile_writeParam(str, QString::number(num), prefix);
}
