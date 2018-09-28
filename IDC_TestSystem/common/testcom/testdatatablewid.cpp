/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "testdatatablewid.h"

TestDataTableWid::TestDataTableWid(QWidget *parent) : ComTableWid(parent)
{
    initWid();
}


void TestDataTableWid::initWid()
{
    QString title = tr("测试数据列表");
    QStringList header;
    header<<tr("状态") << tr("检查项目") << tr("测试项目描述") << tr("期望值") << tr("实测值") << tr("结果");
    initTableWid(header, 0, title);
}

void TestDataTableWid::startSLot()
{
    delTable();
    mList.clear();
}

int TestDataTableWid::getList(QList<QStringList> &list)
{
    list = mList;
    return list.size();
}

void TestDataTableWid::appendItem(const sTestDataItem &item)
{
    QStringList listStr;

    if(item.status) listStr << "√"; else listStr << "×";
    listStr << item.test.item;
    listStr << item.test.subItem;
    listStr << item.expect;
    listStr << item.measured;
    listStr << item.result;
    appendTableRow(listStr, item.status);

    listStr.insert(0, QString::number(item.id));
    mList.append(listStr);
}

void TestDataTableWid::overSLot()
{

}
