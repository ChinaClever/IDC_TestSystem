#include "testitems.h"

TestItems::TestItems()
{
    mId = 1;
    mSpec = nullptr;
}

void TestItems::bulidItems(sDutSpec &spec)
{

}

void TestItems::communication(QList<sTestItem> &items)
{
    sTestItem item;

    item.item = tr("通讯检查");

    item.id = mId++;
    item.subItem = tr("Modbus通讯测试");
    item.eResult = tr("通过Modbus能获取到设备数据");
    items << item;

    item.isSnmp = isSnmp;
    if(isSnmp) {
        item.id = mId++;
        item.subItem = tr("SNMP通讯测试");
        item.eResult = tr("通过SNMP能获取到设备数据");
        items << item;
    }
}


void TestItems::unitItem(QString &itemStr, int num, QList<sTestItem> &items)
{
    sTestItem item;
    QString str = itemStr;

    item.item = tr("%1检查").arg(str);
    for(int i=0; i<num; ++i) {
        item.id = mId++;
        item.subItem = tr("测%1 %2").arg(str).arg(i+1);
        item.eResult = tr("%1 %2 值与负载测试柜值在误差范围内").arg(str).arg(i+1);
        items << item;
    }

    item.item = tr("%1告警检查").arg(itemStr);
    for(int i=0; i<num; ++i) {
        item.id = mId++;
        item.subItem = tr("%1 %2 下限告警测试").arg(str).arg(i+1);
        item.eResult = tr("%1 %2 最小值大于实际值").arg(str).arg(i+1);
        items << item;

        item.id = mId++;
        item.subItem = tr("%1 %2 上限告警测试").arg(str).arg(i+1);
        item.eResult = tr("%1 %2 最大值小于实际值").arg(str).arg(i+1);
        items << item;
    }
}

void TestItems::objData(QString &itemStr, QList<sTestItem> &items, bool v, int num)
{
    QString str;

    if(v) {
        str = itemStr + tr("电压");
        unitItem(str, num, items);
    }

    str = itemStr + tr("电流");
    unitItem(str, num, items);

    sTestItem item;
    item.item = tr("%1功率检查").arg(itemStr);
    for(int i=0; i<num; ++i) {
        item.id = mId++;
        item.subItem = tr("测%1 %2 功率").arg(itemStr).arg(i+1);
        item.eResult = tr("%1 %2 功率值与负载测试柜值在误差范围内").arg(str).arg(i+1);
        items << item;
    }

    item.item = tr("%1开关检查").arg(itemStr);
    for(int i=0; i<num; ++i) {
        item.id = mId++;
        item.subItem = tr("测%1 %2 关").arg(itemStr).arg(i+1);
        item.eResult = tr("%1 %2 继电器是否断开").arg(str).arg(i+1);
        items << item;

        item.id = mId++;
        item.subItem = tr("测%1 %2 开").arg(itemStr).arg(i+1);
        item.eResult = tr("%1 %2 继电器是否接通").arg(str).arg(i+1);
        items << item;
    }


    item.item = tr("%1电能清除检查").arg(itemStr);
    for(int i=0; i<num; ++i) {
        item.id = mId++;
        item.subItem = tr("测%1 %2 电能清零状态").arg(itemStr).arg(i+1);
        item.eResult = tr("%1 %2 电能值是否为零").arg(str).arg(i+1);
        items << item;
    }


}


void TestItems::lineVol(QList<sTestItem> &items)
{
    sTestItem item;

    item.item = tr("相电压检查");

    item.id = mId++;
    item.subItem = tr("读相电压 L%1");
    item.eResult = tr("相电压 L%1 值与负载测试柜电压值在误差范围内");
    items << item;

    item.id = mId++;
    item.subItem = tr("相电压欠压测试");
    item.eResult = tr("相电压最小值大于实际值");
    items << item;

    item.id = mId++;
    item.subItem = tr("相电压过压测试");
    item.eResult = tr("相电压最大值小于实际值");
    items << item;
}

void TestItems::lineCur(QList<sTestItem> &items)
{
    sTestItem item;

    item.item = tr("相电流检查");

    item.id = mId++;
    item.subItem = tr("读相电流");
    item.eResult = tr("相电压值与负载测试柜电压值在误差范围内");
    items << item;

    item.id = mId++;
    item.subItem = tr("相电流下限告警测试");
    item.eResult = tr("相电流最小值大于实际值");
    items << item;

    item.id = mId++;
    item.subItem = tr("相电流上限告警");
    item.eResult = tr("相电流最大值小于实际值");
    items << item;
}
