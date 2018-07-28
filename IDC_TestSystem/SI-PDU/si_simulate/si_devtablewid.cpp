/*
 * Si 设备信息实时显示表格
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "si_devtablewid.h"

SI_DevTableWid::SI_DevTableWid(QWidget *parent) : ComTableWid(parent)
{
    initWid();
    timer = new QTimer(this);
    timer->start(1*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}

/**
 * @brief 初始化表格
 */
void SI_DevTableWid::initWid()
{
    QString title = tr("设备实时信息");
    QStringList header;
    header << tr("设备号") << tr("相数")  << tr("开关")
           << tr("电压") << tr("电流") << tr("视在功率")
           << tr("有功功率") << tr("功率因素") << tr("电能");
    initTableWid(header, 1, title);
}

/**
 * @brief 设置设备名称
 * @param row 行号
 * @param column   列号
 * @param id
 */
void SI_DevTableWid::setDevName(int row, int column, int id)
{
    QString name =tr("%1").arg(id+1);
    setTableItem(row, column, name);
}

/**
 * @brief 设备相数
 * @param row 行号
 * @param column 列号
 * @param id 设备号
 * @param line 相数
 */
void SI_DevTableWid::setLine(int row, int column, int id, int line)
{
    QString name =tr("L%1").arg(line+1);
    setTableItem(row, column, name);
}


/**
 * @brief 获取设备数据包
 * @param id 设备号
 * @return
 */
SI_Rtu_Recv *SI_DevTableWid::getPacket(int id)
{
    return &(SIDataPackets::bulid()->getDev(id)->rtuData);
}

/**
 * @brief 更新开关状态
 * @param row 行号
 * @param column 列号
 * @param id 设备号
 * @param line 相数
 */
void SI_DevTableWid::setSw(int row, int column, int id, int line)
{
    QString str = "---";
    int alarm = 0;

    int value = getPacket(id)->data.sw[line];
    if(value == 0) {
        str = tr("断开");
        alarm = 2;
    } else  {
        str = tr("闭合");
    }

    setTableItem(row, column, str);
    setItemColor(row, column, alarm);
}

/**
 * @brief 设置电压值
 * @param row 行号
 * @param column 列号
 * @param id 设备号
 * @param line 相数
 */
void SI_DevTableWid::setVolValue(int row, int column, int id, int line)
{
    QString str = "---";
    SI_sDataUnit *unit = &(getPacket(id)->data.vol);
    double value = unit->value[line] / COM_RATE_VOL;
    if(value >= 0)
        str = QString::number(value) + "V";

    setTableItem(row, column, str);
    setItemColor(row, column, unit->alarm[line]);
}

/**
 * @brief 设置电流值
 * @param row 行号
 * @param column 列号
 * @param id 设备号
 * @param line 相数
 */
void SI_DevTableWid::setCurValue(int row, int column, int id, int line)
{
    QString str = "---";
    SI_sDataUnit *unit = &(getPacket(id)->data.cur);
    double value = unit->value[line] / COM_RATE_CUR;
    if(value >= 0)
        str = QString::number(value) + "A";

    setTableItem(row, column, str);
    setItemColor(row, column, unit->alarm[line]);
}

/**
 * @brief 设置功率
 * @param row 行号
 * @param column 列号
 * @param id 设备号
 * @param line 相数
 */
void SI_DevTableWid::setPow(int row, int column, int id, int line)
{
    QString str = "---";
    double value = getPacket(id)->data.pow[line] / COM_RATE_POW;
    if(value >= 0)
        str = QString::number(value) + "KVA";

    setTableItem(row, column, str);
}

/**
 * @brief 设置有功功率
 * @param row 行号
 * @param column 列号
 * @param id 设备号
 * @param line 相数
 */
void SI_DevTableWid::setActivePow(int row, int column, int id, int line)
{
    QString str = "---";
    double value = getPacket(id)->data.activePow[line] / COM_RATE_POW;
    if(value >= 0)
        str = QString::number(value) + "KW";

    setTableItem(row, column, str);
}

/**
 * @brief 设置功率因素
 * @param row 行号
 * @param column 列号
 * @param id 设备号
 * @param line 相数
 */
void SI_DevTableWid::setPf(int row, int column, int id, int line)
{
    QString str = "---";
    double value = getPacket(id)->data.pf[line] / COM_RATE_PF;
    if(value >= 0)
        str = QString::number(value);

    setTableItem(row, column, str);
}

/**
 * @brief 设置电能
 * @param row 行号
 * @param column 列号
 * @param id 设备号
 * @param line 相数
 */
void SI_DevTableWid::setEle(int row, int column, int id, int line)
{
    QString str = "---";
    double value = getPacket(id)->data.ele[line] / COM_RATE_ELE;
    if(value >= 0)
        str = QString::number(value) + "KWh";

    setTableItem(row, column, str);
}

/**
 * @brief 检查行数
 */
void SI_DevTableWid::checkRowCount()
{
    int row = 0;
    int devNum = SiConfigFile::bulid()->item->devNum;
    for(int i=0; i<devNum; ++i)
    {
        SiDevPacket *packet = SIDataPackets::bulid()->getDev(i);
        int line = packet->rtuData.data.lineNum;
        if((line<1) || (line>3)) line = packet->rtuData.data.lineNum = 1;
        for(int j=0; j<line; ++j)  {
            row++;
        }
    }
    checkTableRow(row);
}

/**
 * @brief 数据更新入口函数
 */
void SI_DevTableWid::updateData()
{
    int row = 0;

    checkRowCount();
    int devNum = SiConfigFile::bulid()->item->devNum;
    for(int i=0; i<devNum; ++i)
    {
        SiDevPacket *packet = SIDataPackets::bulid()->getDev(i);
        if(packet->rtuData.offLine)
        {
            int line = packet->rtuData.data.lineNum;
            for(int j=0; j<line; ++j)
            {
                int k=0;
                setDevName(row, k++, i);
                setLine(row, k++, i, j);
                setSw(row, k++, i, j);

                setVolValue(row, k++, i, j);
                setCurValue(row, k++, i, j);
                setPow(row, k++, i, j);

                setActivePow(row, k++, i, j);
                setPf(row, k++, i, j);
                setEle(row, k++, i, j);
            }
            row++;
        } else {
            clearRow(row);
        }
    }
}



void SI_DevTableWid::timeoutDone()
{
    updateData();
}
