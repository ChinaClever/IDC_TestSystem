#ifndef SERIALNUMTESTDLG_H
#define SERIALNUMTESTDLG_H

#include <QDialog>
#include "testconfig.h"

namespace Ui {
class TestSerialNumDlg;
}


class TestSerialNumDlg : public QDialog
{
    Q_OBJECT

public:
    explicit TestSerialNumDlg(QWidget *parent = 0);
    ~TestSerialNumDlg();

    sSerialNumItem *getSerialNum();

protected:
    void initWid();
    bool inputCheck();

private slots:
    void on_batchComboBox_currentTextChanged(const QString &arg1);
    void on_purposeComboBox_currentTextChanged(const QString &arg1);
    void on_okBtn_clicked();
    void on_cancelBtn_clicked();

private:
    Ui::TestSerialNumDlg *ui;
    TestConfig *mTestConfig;
    sSerialNumItem *mItem;
};

#endif // SERIALNUMTESTDLG_H