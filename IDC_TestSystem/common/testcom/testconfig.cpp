/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "testconfig.h"

TestConfig::TestConfig()
{
    item = new sTestConfigItem();
}

void TestConfig::initConfig(sSerialNumItem *it)
{
    if(!it) it = &(item->serialNum);

    it->op = getOp();
    it->cn = getCn();
    it->spec = getSpec();
    it->line = getLine();
    it->loop = getLoop();
    it->output = getOutput();

    it->barCode = getBarCode();
    it->batch = getBatch();
    it->purpose = getPurpose();
    it->snClear = getSnClear();
}

void TestConfig::saveConfig(sSerialNumItem *it)
{
    if(!it) it = &(item->serialNum);

    setOp(it->op);
    setCn(it->cn);
    setSpec(it->spec);
    setLine(it->line );
    setLoop(it->loop);
    setOutput(it->output);

    setBarCode(it->barCode);
    setBatch(it->batch);
    setPurpose(it->purpose);
    setSnClear(it->snClear);
}


void TestConfig::setSpec(int value)
{
    QString prefix = getPrefix();
    QString str = QString("%1_spec").arg(prefix);
    sys_configFile_writeParam(str, QString::number(value), prefix);
}

int TestConfig::getSpec()
{
    QString prefix = getPrefix();
    QString str = QString("%1_spec").arg(prefix);
    int ret = sys_configFile_readInt(str, prefix);
    if(ret < 0)  ret = 4;
    return ret;
}


void TestConfig::setLine(int value)
{
    QString prefix = getPrefix();
    QString str = QString("%1_line").arg(prefix);
    sys_configFile_writeParam(str, QString::number(value), prefix);
}

int TestConfig::getLine()
{
    QString prefix = getPrefix();
    QString str = QString("%1_line").arg(prefix);
    int ret = sys_configFile_readInt(str, prefix);
    if(ret < 0)  ret = 3;
    return ret;
}


void TestConfig::setLoop(int value)
{
    QString prefix = getPrefix();
    QString str = QString("%1_loop").arg(prefix);
    sys_configFile_writeParam(str, QString::number(value), prefix);
}

int TestConfig::getLoop()
{
    QString prefix = getPrefix();
    QString str = QString("%1_loop").arg(prefix);
    int ret = sys_configFile_readInt(str, prefix);
    if(ret < 0)  ret = 2;
    return ret;
}


void TestConfig::setOutput(int value)
{
    QString prefix = getPrefix();
    QString str = QString("%1_output").arg(prefix);
    sys_configFile_writeParam(str, QString::number(value), prefix);
}

int TestConfig::getOutput()
{
    QString prefix = getPrefix();
    QString str = QString("%1_output").arg(prefix);
    int ret = sys_configFile_readInt(str, prefix);
    if(ret < 0)  ret = 24;
    return ret;
}


QString TestConfig::getOp()
{
    QString prefix = getPrefix();
    QString str = QString("%1_op").arg(prefix);
    return sys_configFile_readStr(str, prefix);
}

void TestConfig::setOp(const QString &arg)
{
    QString prefix = getPrefix();
    QString str = QString("%1_op").arg(prefix);
    sys_configFile_writeParam(str, arg, prefix);
}


QString TestConfig::getCn()
{
    QString prefix = getPrefix();
    QString str = QString("%1_cn").arg(prefix);
    return sys_configFile_readStr(str, prefix);
}

void TestConfig::setCn(const QString &arg)
{
    QString prefix = getPrefix();
    QString str = QString("%1_cn").arg(prefix);
    sys_configFile_writeParam(str, arg, prefix);
}


QString TestConfig::getBarCode()
{
    QString prefix = getPrefix();
    QString str = QString("%1_barcode").arg(prefix);
    return sys_configFile_readStr(str, prefix);
}

void TestConfig::setBarCode(const QString &arg)
{
    QString prefix = getPrefix();
    QString str = QString("%1_barcode").arg(prefix);
    sys_configFile_writeParam(str, arg, prefix);
}


QString TestConfig::getBatch()
{
    QString prefix = getPrefix();
    QString str = QString("%1_batch").arg(prefix);
    return sys_configFile_readStr(str, prefix);
}

void TestConfig::setBatch(const QString &arg)
{
    QString prefix = getPrefix();
    QString str = QString("%1_batch").arg(prefix);
    sys_configFile_writeParam(str, arg, prefix);
}

QString TestConfig::getPurpose()
{
    QString prefix = getPrefix();
    QString str = QString("%1_purpose").arg(prefix);
    return sys_configFile_readStr(str, prefix);
}

void TestConfig::setPurpose(const QString &arg)
{
    QString prefix = getPrefix();
    QString str = QString("%1_purpose").arg(prefix);
    sys_configFile_writeParam(str, arg, prefix);
}


/**
 * @brief 获取相数
 * @return
 */
bool TestConfig::getSnClear()
{
    bool ret = true;
    QString prefix = getPrefix();
    QString str = QString("%1_snclear").arg(prefix);
    int rtn = sys_configFile_readInt(str, prefix);
    if(rtn == 0)  ret = false;
    return ret;
}

/**
 * @brief 设置相数
 * @param num
 */
void TestConfig::setSnClear(bool mode)
{
    int ret = 0;
    if(mode) ret = 1;
    QString prefix = getPrefix();
    QString str = QString("%1_snclear").arg(prefix);
    sys_configFile_writeParam(str, QString::number(ret), prefix);
}
