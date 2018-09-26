#ifndef SERIALNUMTESTDLG_H
#define SERIALNUMTESTDLG_H

#include <QDialog>
#include "common.h"

namespace Ui {
class SerialNumTestDlg;
}

enum {
    Test_Dev_Zpdu,
    Test_Dev_Mpdu,
    Test_Dev_IPpdu,
    Test_Dev_SIpdu,
    Test_Dev_SIBusBar,
    Test_Dev_IPBusBar,
};

struct sSerialNum
{
    QString name;
    QString op; // 操作员
    QString cn; // 电脑号
    QString sn; // 产品条码

    QString barCode; // 工状条码
    QString batch; // 批次
    QString purpose;
    QDate date;

    bool snClear;
    bool errStop;
    bool isSave;
};

class SerialNumTestDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SerialNumTestDlg(QWidget *parent = 0);
    ~SerialNumTestDlg();

    sSerialNum getSerialNum();

protected:
    bool inputCheck();

private slots:
    void on_batchComboBox_currentTextChanged(const QString &arg1);
    void on_purposeComboBox_currentTextChanged(const QString &arg1);
    void on_okBtn_clicked();
    void on_cancelBtn_clicked();

private:
    Ui::SerialNumTestDlg *ui;
    sSerialNum mSerialNum;
};

#endif // SERIALNUMTESTDLG_H
