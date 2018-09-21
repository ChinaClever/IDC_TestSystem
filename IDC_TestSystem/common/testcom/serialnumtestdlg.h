#ifndef SERIALNUMTESTDLG_H
#define SERIALNUMTESTDLG_H

#include <QDialog>
#include "common.h"

namespace Ui {
class SerialNumTestDlg;
}

class SerialNumTestDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SerialNumTestDlg(QWidget *parent = 0);
    ~SerialNumTestDlg();

private:
    Ui::SerialNumTestDlg *ui;
};

#endif // SERIALNUMTESTDLG_H
