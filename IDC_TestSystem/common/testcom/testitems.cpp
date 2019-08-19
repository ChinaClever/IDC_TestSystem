/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "testitems.h"

TestItems::TestItems()
{
    mSpec = nullptr;
}

bool TestItems::bulidItems(sDutSpec *spec, QList<sTestItem> &items)
{
    mId = 1;
    mSpec = spec;

    communication(items);
    devInfoObjData(items);
    volObjData(tr("电压"),items);
    curObjData(tr("电流"),items);
    powObjData(tr("功率"),items);
    if(mSpec->spec != 1) {
        swObjData(tr("输出位"), mSpec->outputNum , items);
    }

    //eleObjData(tr("电能"),items);
    temhumObjData(items);
    sensorsObjData(items);
    bigCurObjData(items);
    return mSpec->isSnmp;
}

void TestItems::communication(QList<sTestItem> &items)
{
    sTestItem item;
    item.isSnmp = mSpec->isSnmp;

    item.item = tr("通讯检查");

    if(item.isSnmp) {
        item.id = mId++;
        item.subItem = tr("SNMP通讯测试");
        item.eResult = tr("通过SNMP能获取到设备数据");
        items << item;
    }

    item.id = mId++;
    item.subItem = tr("Modbus通讯测试");
    item.eResult = tr("通过Modbus能获取到设备数据");
    items << item;
}


void TestItems::unitItem(const QString &itemStr, int num, QList<sTestItem> &items)
{
    sTestItem item;
    QString str = itemStr;

    item.isSnmp = mSpec->isSnmp;
    item.item = tr("%1检查").arg(str);
    for(int i=0; i<num; ++i) {
        item.id = mId++;
        item.subItem = tr("测%1 %2").arg(str).arg(i+1);
        item.eResult = tr("%1 %2 电流值与负载测试柜值在误差范围内").arg(str).arg(i+1);
        items << item;
    }
}

void TestItems::nocurUnitItem(const QString &itemStr, int num, QList<sTestItem> &items)
{
    sTestItem item;
    QString str = itemStr;

    item.isSnmp = mSpec->isSnmp;
    item.item = tr("%1检查").arg(str);
    for(int i=0; i<num; ++i) {
        item.id = mId++;
        item.subItem = tr("测%1 %2").arg(str).arg(i+1);
        item.eResult = tr("无接负载，%1 %2 值是否为0A").arg(str).arg(i+1);
        items << item;
    }
}

void TestItems::volObjData(const QString & itemStr ,QList<sTestItem> &items)
{

    QString str;

    str =  tr("相")+ itemStr;
    unitItem(str, mSpec->lineNum, items);


    str = tr("回路") + itemStr;
    unitItem(str, mSpec->loopNum, items);

    str =  tr("相")+ itemStr;
    maxminObjData(str , mSpec->lineNum , items);
}

void TestItems::curObjData(const QString & itemStr,QList<sTestItem> &items)
{
    QString str;
    str = tr("相") + itemStr;
    nocurUnitItem(str, mSpec->lineNum, items);

    str = tr("回路") + itemStr;
    nocurUnitItem(str, mSpec->loopNum, items);

    if(mSpec->spec != 3)
    {
        str = tr("输出位")+ itemStr;
        nocurUnitItem(str, mSpec->outputNum, items);
    }


    sTestItem item;
    if(mSpec->lineNum > 1)
    {
        item.isSnmp = mSpec->isSnmp;
        item.item = tr("相电流检查");
        item.id = mId++;
        item.subItem = tr("相总电流检查");
        item.eResult = tr("相总电流值与负载测试柜值在误差范围内");
        items << item;
    }

    str = tr("相") + itemStr;
    unitItem(str, mSpec->lineNum, items);

    if(mSpec->loopNum > 1)
    {
        item.item = tr("回路电流检查");
        item.id = mId++;
        item.subItem = tr("回路总电流检查");
        item.eResult = tr("回路总电流值与负载测试柜值在误差范围内");
        items << item;
    }

    str = tr("回路") + itemStr;
    unitItem(str, mSpec->loopNum, items);

    if(mSpec->spec != 3)
    {
        str = tr("输出位")+ itemStr;
        unitItem(str, mSpec->outputNum, items);
    }

    str = tr("相") + itemStr;
    maxminObjData(str, mSpec->lineNum, items);

    str = tr("回路") + itemStr;
    maxminObjData(str, mSpec->loopNum, items);

    if(mSpec->spec != 3)
    {
        str = tr("输出位")+ itemStr;
        maxminObjData(str, mSpec->outputNum, items);
    }
}

void TestItems::maxminObjData(const QString &itemStr,int num , QList<sTestItem> &items)
{
    sTestItem item;
    QString str = itemStr;
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

void TestItems::swObjData(const QString &itemStr,int num , QList<sTestItem> &items)
{
    QString str;
    sTestItem item;
    item.isSnmp = mSpec->isSnmp;

    if(mSpec->spec != 2) {
        item.item = tr("%1开关检查").arg(itemStr);
        for(int i=0; i<num; ++i) {
            item.id = mId++;
            item.subItem = tr("测%1 %2 断开").arg(itemStr).arg(i+1);
            item.eResult = tr("%1 %2 继电器是否断开").arg(str).arg(i+1);
            items << item;
        }
    }
}

void TestItems::powObjData(const QString & itemStr,QList<sTestItem> &items)
{
    QString str;
    str = tr("相") + itemStr;
    powUnitItem(str, mSpec->lineNum, items);

    str = tr("回路") + itemStr;
    powUnitItem(str, mSpec->loopNum, items);

    if(mSpec->spec != 3)
    {
        str = tr("输出位")+ itemStr;
        powUnitItem(str, mSpec->outputNum, items);
    }
}

void TestItems::powUnitItem(const QString & itemStr,int num , QList<sTestItem> &items)
{
    sTestItem item;
    item.item = tr("%1检查").arg(itemStr);
    for(int i=0; i<num; ++i) {
        item.id = mId++;
        item.subItem = tr("测%1 %2 功率").arg(itemStr).arg(i+1);
        item.eResult = tr("%1 %2 功率值与负载测试柜值在误差范围内").arg(itemStr).arg(i+1);
        items << item;
    }
}

void TestItems::eleObjData(const QString & itemStr,QList<sTestItem> &items)
{//先清开关位电能，接着清回路和相电能
    QString str;
    if(mSpec->spec != 3)
    {
        str = tr("输出位")+ itemStr;
        eleUnitItem(str, mSpec->outputNum, items);
    }
    str = tr("回路") + itemStr;
    eleUnitItem(str, mSpec->loopNum, items);

    str = tr("相") + itemStr;
    eleUnitItem(str, mSpec->lineNum, items);
}

void TestItems::eleUnitItem(const QString & itemStr,int num , QList<sTestItem> &items)
{
    sTestItem item;
    item.item = tr("%1电能清除检查").arg(itemStr);
    for(int i=0; i<num; ++i) {
        item.id = mId++;
        item.subItem = tr("测%1 %2 电能清零状态").arg(itemStr).arg(i+1);
        item.eResult = tr("%1 %2 电能值是否为零").arg(itemStr).arg(i+1);
        items << item;
    }
}

void TestItems::temhumObjData(QList<sTestItem> &items)
{//暂时把温湿度传感器写死为4                     2019/7/25 peng
    sTestItem item;
    int num = 4;
    for(int k = 0 ; k < 2 ; ++k)
    {
        item.item = (k == 0 )? tr("温度检查"):tr("湿度检查");
        QString itemStr = (k == 0 )? tr("温度"):tr("湿度");
        for(int i=0; i<num; ++i) {
            item.id = mId++;
            item.subItem = tr("测%1 %2").arg(itemStr).arg(i+1);
            item.eResult = tr("%1 %2 与负载测试柜值在误差范围内").arg(itemStr).arg(i+1);
            items << item;
        }
    }
}

void TestItems::sensorsObjData(QList<sTestItem> &items)
{//暂时把门禁写死为2                     2019/7/25 peng
    sTestItem item;

    int num = 2;
    item.item = tr("门禁检查");
    QString itemStr = tr("门禁");
    for(int i = 0; i < num; ++i) {
        item.id = mId++;
        item.subItem = tr("测%1 %2").arg(itemStr).arg(i+1);
        item.eResult = tr("%1 %2 是否正常").arg(itemStr).arg(i+1);
        items << item;
    }
    item.item = tr("烟雾检查");
    itemStr = tr("烟雾");
    item.id = mId++;
    item.subItem = tr("测%1").arg(itemStr);
    item.eResult = tr("%1 是否正常").arg(itemStr);
    items << item;

    item.item = tr("水浸检查");
    itemStr = tr("水浸");
    item.id = mId++;
    item.subItem = tr("测%1").arg(itemStr);
    item.eResult = tr("%1 是否正常").arg(itemStr);
    items << item;
}

void TestItems::devInfoObjData(QList<sTestItem> &items)
{
    sTestItem item;

    item.item = tr("设备基本检查");
    for(int k = 0 ; k < 4 ; ++k)
    {
        QString itemStr =  tr("设备系列");
        switch (k) {
        case 0:break;
        case 1:itemStr = tr("相");break;
        case 2:itemStr = tr("回路");break;
        case 3:itemStr = tr("输出");break;
        default:
            break;
        }
        if(k > 0) itemStr += tr("数量");
        item.id = mId++;
        item.subItem = tr("%1测试").arg(itemStr);
        item.eResult = tr("输入信息%1，与PDU信息是否一致").arg(itemStr);
        items << item;
    }
}

void TestItems::bigCurObjData(QList<sTestItem> &items)
{
    if(mSpec->spec != 3)
    {
        QString str = tr("大电流输出位");
        unitItem(str, mSpec->outputNum, items);
        powUnitItem(str, mSpec->outputNum, items);
    }
}
