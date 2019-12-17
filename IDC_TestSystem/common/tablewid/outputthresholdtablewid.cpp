#include "outputthresholdtablewid.h"

OutputThresholdTableWid::OutputThresholdTableWid(QWidget *parent) : OutputTableWid(parent)
{
    initWid();
}


void OutputThresholdTableWid::initWid()
{
   QString title = tr("输出位阈值信息");
   QStringList header;
   header << tr("设备号") << tr("输出位")
          << tr("电流") << tr("最小值") << tr("临界下限")
          << tr("临界上限") << tr("最大值");
   initTableWid(header, 1, title);
}


void OutputThresholdTableWid::setAlarm(sObjData &unit, int row)
{
   int value = unit.cur.alarm;
   if(value) value = 2;
   else value = unit.cur.crAlarm;
   setItemColor(row, 2, value);
}

double OutputThresholdTableWid::autoRate(int vol)
{
    double ret = 1;
    if(vol > 1000 && vol < 3000) {
        ret = 0.1;
    }
    mRate = ret;

    return ret;
}

void OutputThresholdTableWid::setObjUnit(sObjData &unit, QStringList &list)
{
   autoRate(unit.vol.value);
   double value = unit.cur.value * mRate/ COM_RATE_CUR;
   list << QString::number(value) + "A";

   value = unit.cur.min * mRate/ COM_RATE_CUR;
   list << QString::number(value) + "A";

   value = unit.cur.crMin * mRate/ COM_RATE_CUR;
   list << QString::number(value) + "A";

   value = unit.cur.crMax * mRate/ COM_RATE_CUR;
   list << QString::number(value) + "A";

   value = unit.cur.max * mRate/ COM_RATE_CUR;
   list << QString::number(value) + "A";
}

