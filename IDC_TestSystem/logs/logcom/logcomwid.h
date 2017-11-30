#ifndef LOGCOMWID_H
#define LOGCOMWID_H

#include <QWidget>
#include "logbtnbar.h"
#include "sqltablemodel.h"
#include "log_datewidget.h"

namespace Ui {
class LogComWid;
}

class LogComWid : public QWidget
{
    Q_OBJECT

public:
    explicit LogComWid(QWidget *parent = 0);
    ~LogComWid();

protected:
    void initBtnBar();
    virtual QString getTableName()=0;
    virtual void initTable()=0;
    bool refreshTable(const QString &table);

protected slots:
    void initFunSLot();
    void doubleSlot(QModelIndex);
    virtual void clearTableSlot()=0;
    void refreshSlot();
    void exportSlot();
    void setGroupBoxTitle(const QString &title);

protected:
    Ui::LogComWid *ui;
    LOG_DateWidget *mDateWidget;

    QString mTableTile;
    QStringList mHeadList;
    LogBtnBar *mBtnBar;
    SqlTableModel *model;
};

#endif // LOGCOMWID_H
