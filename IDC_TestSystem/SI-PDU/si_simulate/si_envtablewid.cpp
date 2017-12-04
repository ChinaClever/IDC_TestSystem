#include "si_envtablewid.h"



SI_EnvTableWid::SI_EnvTableWid(QWidget *parent) : ComTableWid(parent)
{
    initWid();
    timer = new QTimer(this);
    timer->start(2*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}

void SI_EnvTableWid::initWid()
{
    QString title = tr("设备环境信息");
    QStringList header;
    header << tr("设备号") << tr("温度") << tr("温度下限") << tr("温度上限")
           << tr("湿度") << tr("湿度下限") << tr("湿度上限");
    initTableWid(header, 4, title);
}


void SI_EnvTableWid::setDevName(int id, int column)
{
    QString name =tr("%1").arg(id+1);
    setTableItem(id, column, name);
}

SI_sDataUnit *SI_EnvTableWid::getTempUnit(int id)
{
    SiDevPacket *packet = SIDataPackets::bulid()->getDev(id);
    SI_sDataUnit *unit = &(packet->rtuData.data.tem);

    return unit;
}


void SI_EnvTableWid::setTempValue(int id, int column)
{
    QString str = "---";
    SI_sDataUnit *unit = getTempUnit(id);
    double value = unit->value[0] / COM_RATE_TEM;
    if(value >= 0)
        str = QString::number(value) + "℃";

    setTableItem(id, column, str);
    setItemColor(id, column, unit->alarm[0]);
}

void SI_EnvTableWid::setTempMin(int id, int column)
{
    QString str = "---";
    SI_sDataUnit *unit = getTempUnit(id);
    double value = unit->min[0] / COM_RATE_TEM;
    if(value >= 0)
        str = QString::number(value) + "℃";

    setTableItem(id, column, str);
}

void SI_EnvTableWid::setTempMax(int id, int column)
{
    QString str = "---";
    SI_sDataUnit *unit = getTempUnit(id);
    double value = unit->max[0] / COM_RATE_TEM;
    if(value >= 0)
        str = QString::number(value) + "℃";

    setTableItem(id, column, str);
}



SI_sDataUnit *SI_EnvTableWid::getHumUnit(int id)
{
    SiDevPacket *packet = SIDataPackets::bulid()->getDev(id);
    SI_sDataUnit *unit = &(packet->rtuData.data.hum);

    return unit;
}


void SI_EnvTableWid::setHumValue(int id, int column)
{
    QString str = "---";
    SI_sDataUnit *unit = getHumUnit(id);
    double value = unit->value[0] / COM_RATE_HUM;
    if(value >= 0)
        str = QString::number(value) + "%";

    setTableItem(id, column, str);
    setItemColor(id, column, unit->alarm[0]);
}

void SI_EnvTableWid::setHumMin(int id, int column)
{
    QString str = "---";
    SI_sDataUnit *unit = getHumUnit(id);
    double value = unit->min[0] / COM_RATE_HUM;
    if(value >= 0)
        str = QString::number(value) + "%";

    setTableItem(id, column, str);
}

void SI_EnvTableWid::setHumMax(int id, int column)
{
    QString str = "---";
    SI_sDataUnit *unit = getHumUnit(id);
    double value = unit->max[0] / COM_RATE_HUM;
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
        SiDevPacket *packet = SIDataPackets::bulid()->getDev(i);
        if(packet->rtuData.offLine)
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