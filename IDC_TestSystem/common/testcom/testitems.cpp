#include "testitems.h"

TestItems::TestItems()
{
    mSpec = nullptr;
    isSnmp = false;
}

void TestItems::bulidItems(sDutSpec *spec, QList<sTestItem> &items)
{
    mId = 1;
    mSpec = spec;
    if(spec->dev > 1) isSnmp = true;

    communication(items);
    objData(tr("相"), items,  mSpec->lineNum);
    objData(tr("回路"), items, mSpec->loopNum);
    if(mSpec->spec !=1) {
        outputObjData(tr("输出位"), items, mSpec->outputNum);
    }
}

void TestItems::communication(QList<sTestItem> &items)
{
    sTestItem item;
    item.isSnmp = isSnmp;

    item.item = tr("通讯检查");

    item.id = mId++;
    item.subItem = tr("Modbus通讯测试");
    item.eResult = tr("通过Modbus能获取到设备数据");
    items << item;

    if(item.isSnmp) {
        item.id = mId++;
        item.subItem = tr("SNMP通讯测试");
        item.eResult = tr("通过SNMP能获取到设备数据");
        items << item;
    }
}


void TestItems::unitItem(const QString &itemStr, int num, QList<sTestItem> &items)
{
    sTestItem item;
    QString str = itemStr;

    item.isSnmp = isSnmp;
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



void TestItems::objData(const QString &itemStr, QList<sTestItem> &items, int num)
{
    QString str;

    str = itemStr + tr("电压");
    unitItem(str, num, items);

    str = itemStr + tr("电流");
    unitItem(str, num, items);

    sTestItem item;
    item.isSnmp = isSnmp;
    item.item = tr("%1功率检查").arg(itemStr);
    for(int i=0; i<num; ++i) {
        item.id = mId++;
        item.subItem = tr("测%1 %2 功率").arg(itemStr).arg(i+1);
        item.eResult = tr("%1 %2 功率值与负载测试柜值在误差范围内").arg(str).arg(i+1);
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


void TestItems::outputObjData(const QString &itemStr, QList<sTestItem> &items, int num)
{
    QString str;
    sTestItem item;
    item.isSnmp = isSnmp;

    if(mSpec->spec !=2) {
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
    }

    if(mSpec->spec !=3) {
        str = itemStr + tr("电流");
        unitItem(str, num, items);

        item.item = tr("%1功率检查").arg(itemStr);
        for(int i=0; i<num; ++i) {
            item.id = mId++;
            item.subItem = tr("测%1 %2 功率").arg(itemStr).arg(i+1);
            item.eResult = tr("%1 %2 功率值与负载测试柜值在误差范围内").arg(str).arg(i+1);
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
}

