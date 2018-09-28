#ifndef TESTDATASAVE_H
#define TESTDATASAVE_H

#include "excel_savethread.h"
#include "testitemtablewid.h"

class TestDataSave : public QObject
{
    Q_OBJECT
public:
    explicit TestDataSave(QObject *parent = nullptr);

    void saveTestData(sSerialNumItem *item, sTestProgress &arg, QList<QStringList> &list);

protected:
    int bulidHead(sSerialNumItem *item);
    int bulidProgressLog(sTestProgress &arg);
    void bulidTestData(QList<QStringList> &list);

private:
    QString bulidFileName(sSerialNumItem *item);
    QString bulidPath(sSerialNumItem *item);

private:
    Excel_SaveThread *mSaveThread;
    QString mFileName;
    QList<QStringList> mList;
};

#endif // TESTDATASAVE_H
