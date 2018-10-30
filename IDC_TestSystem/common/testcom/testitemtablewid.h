#ifndef TESTITEMTABLEWID_H
#define TESTITEMTABLEWID_H
#include "testitems.h"


class TestItemTableWid : public ComTableWid
{
    Q_OBJECT
public:
    explicit TestItemTableWid(QWidget *parent = nullptr);

     void init(sTestConfigItem *item) { mItem = item;}

signals:
     void allNumsSig(int nums);

public slots:
    void startSlot();

protected:
    void initWid();
    int updateWid(sDataPacket &packet);
    void appendItem(const sTestItem &item);

private:
    int mCount;
    TestItems *mTestItems;
    sTestConfigItem  *mItem;
};

#endif // TESTITEMTABLEWID_H
