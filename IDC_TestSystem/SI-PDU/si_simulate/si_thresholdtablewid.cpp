/*
 * Si 设备阈值实时显示表格
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "si_thresholdtablewid.h"

SI_ThresholdTableWid::SI_ThresholdTableWid(QWidget *parent) : ComTableWid(parent)
{
    initWid();
    timer = new QTimer(this);
    timer->start(1*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}

/**
 * @brief 初始化表格
 */
void SI_ThresholdTableWid::initWid()
{
    QString title = tr("设备阈值信息");
    QStringList header;
    header << tr("设备号") << tr("相数")
           << tr("电压") << tr("电压下限") << tr("电压上限")
           << tr("电流") << tr("电流下限") << tr("电流上限");
    initTableWid(header, 4, title);
}

/**
 * @brief 设备设备表
 * @param row
 * @param column
 * @param id
 */
void SI_ThresholdTableWid::setDevName(int row, int column, int id)
{
    QString name =tr("%1").arg(id+1);
    setTableItem(row, column, name);
}

/**
 * @brief 设备相数
 * @param row 行号
 * @param column 列号
 * @param id  设备号
 * @param line 相数
 */
void SI_ThresholdTableWid::setLine(int row, int column, int id, int line)
{
    QString name =tr("L%1").arg(line+1);
    setTableItem(row, column, name);
}


sDataUnit *SI_ThresholdTableWid::getVolUnit(int id, int line)
{
    sDataPacket *packet = SIDataPackets::bulid()->getDev(id);
    sDataUnit *unit = &(packet->data.line[line].vol);

    return unit;
}

/**
 * @brief 设置电压值
 * @param row 行号
 * @param column 列号
 * @param id  设备号
 * @param line 相数
 */
void SI_ThresholdTableWid::setVolValue(int row, int column, int id, int line)
{
    QString str = "---";
    sDataUnit *unit = getVolUnit(id, line);
    double value = unit->value / COM_RATE_VOL;
    if(value >= 0)
        str = QString::number(value) + "V";

    setTableItem(row, column, str);
    setItemColor(row, column, unit->alarm);
}

/**
 * @brief 设置电压最小值
 * @param row 行号
 * @param column 列号
 * @param id  设备号
 * @param line 相数
 */
void SI_ThresholdTableWid::setVolMin(int row, int column, int id, int line)
{
    QString str = "---";
    sDataUnit *unit = getVolUnit(id, line);
    double value = unit->min / COM_RATE_VOL;
    if(value >= 0)
        str = QString::number(value) + "V";

    setTableItem(row, column, str);
}

/**
 * @brief 设置电压最大值
 * @param row 行号
 * @param column 列号
 * @param id  设备号
 * @param line 相数
 */
void SI_ThresholdTableWid::setVolMax(int row, int column, int id, int line)
{
    QString str = "---";
    sDataUnit *unit = getVolUnit(id, line);
    double value = unit->max / COM_RATE_VOL;
    if(value >= 0)
        str = QString::number(value) + "V";

    setTableItem(row, column, str);
}



sDataUnit *SI_ThresholdTableWid::getCurUnit(int id, int line)
{
    sDataPacket *packet = SIDataPackets::bulid()->getDev(id);
    sDataUnit *unit = &(packet->data.line[line].vol);

    return unit;
}

/**
 * @brief 电流值
 * @param row 行号
 * @param column 列号
 * @param id  设备号
 * @param line 相数
 */
void SI_ThresholdTableWid::setCurValue(int row, int column, int id, int line)
{
    QString str = "---";
    sDataUnit *unit = getCurUnit(id, line);
    double value = unit->value / COM_RATE_CUR;
    if(value >= 0)
        str = QString::number(value) + "A";

    setTableItem(row, column, str);
    setItemColor(row, column, unit->alarm);
}

/**
 * @brief 电流最小值
 * @param row 行号
 * @param column 列号
 * @param id  设备号
 * @param line 相数
 */
void SI_ThresholdTableWid::setCurMin(int row, int column, int id, int line)
{
    QString str = "---";
    sDataUnit *unit = getCurUnit(id, line);
    double value = unit->min / COM_RATE_CUR;
    if(value >= 0)
        str = QString::number(value) + "A";

    setTableItem(row, column, str);
}

/**
 * @brief 电流最大值
 * @param row 行号
 * @param column 列号
 * @param id  设备号
 * @param line 相数
 */
void SI_ThresholdTableWid::setCurMax(int row, int column, int id, int line)
{
    QString str = "---";
    sDataUnit *unit = getCurUnit(id, line);
    double value = unit->max / COM_RATE_CUR;
    if(value >= 0)
        str = QString::number(value) + "A";

    setTableItem(row, column, str);
}


void SI_ThresholdTableWid::checkRowCount()
{
    int row = 0;
    int devNum = SiConfigFile::bulid()->item->devNum;
    for(int i=0; i<devNum; ++i)
    {
        sDataPacket *packet = SIDataPackets::bulid()->getDev(i);
        int line = packet->data.lineNum;
        if((line<1) || (line>3)) line = packet->data.lineNum = 1;
        for(int j=0; j<line; ++j)
        {
            row++;
        }
    }
    checkTableRow(row);
}

/**
 * @brief 数据更新入口函数
 */
void SI_ThresholdTableWid::updateData()
{
    int row = 0;

    checkRowCount();
    int devNum = SiConfigFile::bulid()->item->devNum;
    for(int i=0; i<devNum; ++i)
    {
        sDataPacket *packet = SIDataPackets::bulid()->getDev(i);
        int line = packet->data.lineNum;
        for(int j=0; j<line; ++j)
        {
            if(packet->offLine)
            {
                int k=0;
                setDevName(row, k++, i);
                setLine(row, k++, i, j);

                setVolValue(row, k++, i, j);
                setVolMin(row, k++, i, j);
                setVolMax(row, k++, i, j);

                setCurValue(row, k++, i, j);
                setCurMin(row, k++, i, j);
                setCurMax(row, k++, i, j);
            } else {
                clearRow(row);
            }
            row++;
        }
    }
}


void SI_ThresholdTableWid::timeoutDone()
{
    updateData();
}
