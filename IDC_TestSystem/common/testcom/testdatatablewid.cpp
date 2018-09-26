#include "testdatatablewid.h"

TestDataTableWid::TestDataTableWid(QWidget *parent) : ComTableWid(parent)
{
    initWid();
}


void TestDataTableWid::initWid()
{
    QString title = tr("测试数据列表");
    QStringList header;
    header << tr("检查项目") << tr("测试项目描述") << tr("期望值") << tr("实测值") << tr("结果");
    initTableWid(header, 0, title);
}
