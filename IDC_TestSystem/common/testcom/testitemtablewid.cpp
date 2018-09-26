#include "testitemtablewid.h"

TestItemTableWid::TestItemTableWid(QWidget *parent) : ComTableWid(parent)
{
    mTestItems = new TestItems;
    initWid();
}


void TestItemTableWid::initWid()
{
    QString title = tr("测试项目列表");
    QStringList header;
    header <<tr("执行") << tr("检查项目") << tr("测试项目描述") << tr("期望结果") << tr("Modubs通讯") << tr("SNMP通讯");
    initTableWid(header, 0, title);
}


void TestItemTableWid::appendItem(const sTestItem &item)
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

void TestItemTableWid::updateWid(sDataPacket &packet)
{
    QList<sTestItem> items;

    sDutSpec spdc;
    spdc.spec = packet.devSpec;
    spdc.lineNum = packet.data.lineNum;
    spdc.loopNum = packet.data.loopNum;
    spdc.outputNum = packet.data.outputNum;

    mTestItems->bulidItems(&spdc, items);
    for( const auto& value : items ) {
        appendItem(value);
    }
}

void TestItemTableWid::startSlot(int devId)
{
    delTable();
    if(mPackets) {
        updateWid(mPackets->dev[devId]);
    }
}
