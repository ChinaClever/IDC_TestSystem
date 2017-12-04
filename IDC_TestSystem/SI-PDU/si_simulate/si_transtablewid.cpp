#include "si_transtablewid.h"

SI_TransTableWid::SI_TransTableWid(QWidget *parent) : ComTableWid(parent)
{
    initWid();
    timer = new QTimer(this);
    timer->start(2*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}


void SI_TransTableWid::initWid()
{
    QString title = tr("命令传输情况");
    QStringList header;
    header << tr("设备号") << tr("状态") << tr("总次数") << tr("成功次数") << tr("失败次数");
    initTableWid(header, 4, title);
}


void SI_TransTableWid::setDevName(int id, int column)
{
    QString name =tr("%1").arg(id+1);
    setTableItem(id, column, name);
}

void SI_TransTableWid::setDevState(int id, int column)
{
    QString str =tr("高线");
    SiDevPacket *packet = SIDataPackets::bulid()->getDev(id);
    if(packet->rtuData.offLine)
        str =tr("在线");

    setTableItem(id, column, str);
}

SiDevPacket *SI_TransTableWid::getPacket(int id)
{
    return SIDataPackets::bulid()->getDev(id);
}


void SI_TransTableWid::setValue(int id, int column, int value)
{
    QString str = "---";
    if(value >= 0) str = QString::number(value);
    setTableItem(id, column, str);
}

void SI_TransTableWid::setAllValue(int id, int column)
{
    int value = getPacket(id)->count.count ;
    setValue(id, column, value);
}

void SI_TransTableWid::setOK(int id, int column)
{
    int value = getPacket(id)->count.okCount ;
    setValue(id, column, value);
}

void SI_TransTableWid::setErr(int id, int column)
{
    int value = getPacket(id)->count.errCount ;
    setValue(id, column, value);
    if(value) {
        setItemColor(id, column, 1);
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
