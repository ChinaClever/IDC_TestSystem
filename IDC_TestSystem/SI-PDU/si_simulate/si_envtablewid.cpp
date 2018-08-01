/*
 * Si 环境信息实时显示表格
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "si_envtablewid.h"



SI_EnvTableWid::SI_EnvTableWid(QWidget *parent) : ComTableWid(parent)
{
    initWid();
    timer = new QTimer(this);
    timer->start(1*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}

/**
 * @brief 初始化表格
 */
void SI_EnvTableWid::initWid()
{
    QString title = tr("设备环境信息");
    QStringList header;
    header << tr("设备号") << tr("温度") << tr("温度下限") << tr("温度上限")
           << tr("湿度") << tr("湿度下限") << tr("湿度上限");
    initTableWid(header, 4, title);
}

/**
 * @brief 设备名称
 * @param id
 * @param column
 */
void SI_EnvTableWid::setDevName(int id, int column)
{
    QString name =tr("%1").arg(id+1);
    setTableItem(id, column, name);
}

/**
 * @brief 获取温度数据结构体
 * @param id
 * @return
 */
sDataUnit *SI_EnvTableWid::getTempUnit(int id)
{
    sDataPacket *packet = SIDataPackets::bulid()->getDev(id);
    sDataUnit *unit = &(packet->data.env.tem[0]);

    return unit;
}

/**
 * @brief 更新温度值
 * @param id
 * @param column
 */
void SI_EnvTableWid::setTempValue(int id, int column)
{
    QString str = "---";
    sDataUnit *unit = getTempUnit(id);
    double value = unit->value / COM_RATE_TEM;
    if(value >= 0)
        str = QString::number(value) + "℃";

    setTableItem(id, column, str);
    setItemColor(id, column, unit->alarm);
}

/**
 * @brief 更新温度最小值
 * @param id
 * @param column
 */
void SI_EnvTableWid::setTempMin(int id, int column)
{
    QString str = "---";
    sDataUnit *unit = getTempUnit(id);
    double value = unit->min / COM_RATE_TEM;
    if(value >= 0)
        str = QString::number(value) + "℃";

    setTableItem(id, column, str);
}

/**
 * @brief 更新温度最大值
 * @param id
 * @param column
 */
void SI_EnvTableWid::setTempMax(int id, int column)
{
    QString str = "---";
    sDataUnit *unit = getTempUnit(id);
    double value = unit->max / COM_RATE_TEM;
    if(value >= 0)
        str = QString::number(value) + "℃";

    setTableItem(id, column, str);
}


/**
 * @brief 获取温度数据结构体
 * @param id
 * @return
 */
sDataUnit *SI_EnvTableWid::getHumUnit(int id)
{
    sDataPacket *packet = SIDataPackets::bulid()->getDev(id);
    sDataUnit *unit = &(packet->data.env.hum[0]);

    return unit;
}

/**
 * @brief 设置温度值
 * @param id
 * @param column
 */
void SI_EnvTableWid::setHumValue(int id, int column)
{
    QString str = "---";
    sDataUnit *unit = getHumUnit(id);
    double value = unit->value / COM_RATE_HUM;
    if(value >= 0)
        str = QString::number(value) + "%";

    setTableItem(id, column, str);
    setItemColor(id, column, unit->alarm);
}

/**
 * @brief 设置温度最小值
 * @param id
 * @param column
 */
void SI_EnvTableWid::setHumMin(int id, int column)
{
    QString str = "---";
    sDataUnit *unit = getHumUnit(id);
    double value = unit->min / COM_RATE_HUM;
    if(value >= 0)
        str = QString::number(value) + "%";

    setTableItem(id, column, str);
}

/**
 * @brief 设置温度最大值
 * @param id
 * @param column
 */
void SI_EnvTableWid::setHumMax(int id, int column)
{
    QString str = "---";
    sDataUnit *unit = getHumUnit(id);
    double value = unit->max / COM_RATE_HUM;
    if(value >= 0)
        str = QString::number(value) + "%";

    setTableItem(id, column, str);
}



/**
 * @brief 数据更新入口函数
 */
void SI_EnvTableWid::updateData()
{
    int row = SiConfigFile::bulid()->item->devNum;
    checkTableRow(row);

    for(int i=0; i<row; ++i)
    {
        sDataPacket *packet = SIDataPackets::bulid()->getDev(i);
        if(packet->offLine)
        {
            int k=0;
            setDevName(i, k++);

            setTempValue(i, k++);
            setTempMin(i, k++);
            setTempMax(i, k++);

            setHumValue(i, k++);
            setHumMin(i, k++);
            setHumMax(i, k++);
        } else {
            clearRow(i);
        }
    }
}

void SI_EnvTableWid::timeoutDone()
{
    updateData();
}
