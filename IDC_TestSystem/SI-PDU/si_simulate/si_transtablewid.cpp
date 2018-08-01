/*
 * Si 传输表格
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "si_transtablewid.h"

SI_TransTableWid::SI_TransTableWid(QWidget *parent) : ComTableWid(parent)
{
    initWid();
    timer = new QTimer(this);
    timer->start(1*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}

/**
 * @brief 初始化表格
 */
void SI_TransTableWid::initWid()
{
    QString title = tr("命令传输情况");
    QStringList header;
    header << tr("设备号") << tr("状态") << tr("总次数") << tr("成功次数") << tr("失败次数");
    initTableWid(header, 4, title);
}

/**
 * @brief 设备表
 * @param id
 * @param column
 */
void SI_TransTableWid::setDevName(int id, int column)
{
    QString name =tr("%1").arg(id+1);
    setTableItem(id, column, name);
}

/**
 * @brief 设备状态
 * @param id
 * @param column
 */
void SI_TransTableWid::setDevState(int id, int column)
{
    QString str =tr("高线");
    sDataPacket *packet = SIDataPackets::bulid()->getDev(id);
    if(packet->offLine)
        str =tr("在线");

    setTableItem(id, column, str);
}

sDataPacket *SI_TransTableWid::getPacket(int id)
{
    return SIDataPackets::bulid()->getDev(id);
}

/**
 * @brief 设置Item
 * @param id
 * @param column
 * @param value
 */
void SI_TransTableWid::setValue(int id, int column, int value)
{
    QString str = "---";
    if(value >= 0) str = QString::number(value);
    setTableItem(id, column, str);
}

/**
 * @brief 传输次数
 * @param id
 * @param column
 */
void SI_TransTableWid::setAllValue(int id, int column)
{
    int value = getPacket(id)->rtuCount.count ;
    setValue(id, column, value);
}

/**
 * @brief 成功次数
 * @param id
 * @param column
 */
void SI_TransTableWid::setOK(int id, int column)
{
    int value = getPacket(id)->rtuCount.okCount ;
    setValue(id, column, value);
}

/**
 * @brief 失败次数
 * @param id
 * @param column
 */
void SI_TransTableWid::setErr(int id, int column)
{
    int value = getPacket(id)->rtuCount.errCount ;
    setValue(id, column, value);
    if(value) {
        setItemColor(id, column, 2);
    }
}


/**
 * @brief 数据更新入口函数
 */
void SI_TransTableWid::updateData()
{
    int row = SiConfigFile::bulid()->item->devNum;
    checkTableRow(row);

    for(int i=0; i<row; ++i)
    {
        int k=0;
        setDevName(i, k++);
        setDevState(i, k++);

        setAllValue(i, k++);
        setOK(i, k++);
        setErr(i, k++);
    }
}

void SI_TransTableWid::timeoutDone()
{
    updateData();
}
