#include "si_devtablewid.h"

SI_DevTableWid::SI_DevTableWid(QWidget *parent) : ComTableWid(parent)
{
    initWid();
    timer = new QTimer(this);
    timer->start(2*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}


void SI_DevTableWid::initWid()
{
    QString title = tr("设备阈值信息");
    QStringList header;
    header << tr("设备号") << tr("相数")  << tr("开关")
           << tr("电压") << tr("电流") << tr("视在功率")
           << tr("有功功率") << tr("功率因素") << tr("电能");
    initTableWid(header, 4, title);
}


void SI_DevTableWid::setDevName(int row, int column, int id)
{
    QString name =tr("%1").arg(id+1);
    setTableItem(row, column, name);
}


void SI_DevTableWid::setLine(int row, int column, int id, int line)
{
    QString name =tr("L%1").arg(line+1);
    setTableItem(row, column, name);
}



SI_Rtu_Recv *SI_DevTableWid::getPacket(int id)
{
    return &(SIDataPackets::bulid()->getDev(id)->rtuData);
}


void SI_DevTableWid::setSw(int row, int column, int id, int line)
{
    QString str = "---";
    int alarm = 0;

    int value = getPacket(id)->data.sw[line];
    if(value == 0) {
        str = tr("断开");
        alarm = 1;
    } else  {
        str = tr("闭合");
    }

    setTableItem(row, column, str);
    setItemColor(row, column, alarm);
}


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


void SI_DevTableWid::setPow(int row, int column, int id, int line)
{
    QString str = "---";
    double value = getPacket(id)->data.pow[line] / COM_RATE_POW;
    if(value >= 0)
        str = QString::number(value) + "KVA";

    setTableItem(row, column, str);
}


void SI_DevTableWid::setActivePow(int row, int column, int id, int line)
{
    QString str = "---";
    double value = getPacket(id)->data.activePow[line] / COM_RATE_POW;
    if(value >= 0)
        str = QString::number(value) + "KVA";

    setTableItem(row, column, str);
}

void SI_DevTableWid::setPf(int row, int column, int id, int line)
{
    QString str = "---";
    double value = getPacket(id)->data.pf[line] / COM_RATE_PF;
    if(value >= 0)
        str = QString::number(value);

    setTableItem(row, column, str);
}

void SI_DevTableWid::setEle(int row, int column, int id, int line)
{
    QString str = "---";
    double value = getPacket(id)->data.ele[line] / COM_RATE_ELE;
    if(value >= 0)
        str = QString::number(value);

    setTableItem(row, column, str);
}

void SI_DevTableWid::checkRowCount()
{
    int row = 0;
    int devNum = SiConfigFile::bulid()->item->devNum;
    for(int i=0; i<devNum; ++i)
    {
        SiDevPacket *packet = SIDataPackets::bulid()->getDev(i);
        int line = packet->rtuData.data.lineNum;
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
void SI_DevTableWid::updateData()
{
    int row = 0;

    checkRowCount();
    int devNum = SiConfigFile::bulid()->item->devNum;
    for(int i=0; i<devNum; ++i)
    {
        SiDevPacket *packet = SIDataPackets::bulid()->getDev(i);
        int line = packet->rtuData.data.lineNum;
        for(int j=0; j<line; ++j)
        {
            if(packet->rtuData.offLine)
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
            } else {
                clearRow(row);
            }
            row++;
        }
    }
}



void SI_DevTableWid::timeoutDone()
{
    updateData();
}
