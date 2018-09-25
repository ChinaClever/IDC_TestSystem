#include "testitemtablewid.h"

TestItemTableWid::TestItemTableWid(QWidget *parent) : ComTableWid(parent)
{
    initWid();
}


void TestItemTableWid::initWid()
{
    QString title = tr("测试项目列表");
    QStringList header;
    header <<tr("执行") << tr("检查项目") << tr("测试项目描述") << tr("期望结果") << tr("Modubs通讯") << tr("SNMP通讯");
    initTableWid(header, 0, title);
}


void TestItemTableWid::appendItem(sTestItem &item)
{
    QStringList listStr;

    if(item.isExecute) listStr << "√"; else listStr << "×";
    listStr << item.item;
    listStr << item.subItem;
    listStr << item.eResult;

    if(item.isModubs) listStr << "√"; else listStr << "";
    if(item.isSnmp) listStr << "√"; else listStr << "";
    appendTableRow(listStr);
}
