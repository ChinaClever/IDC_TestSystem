#ifndef SISETMODBUSCMDDLG_H
#define SISETMODBUSCMDDLG_H

#include <QDialog>

namespace Ui {
class SiSetModbusCmdDlg;
}

class SiSetModbusCmdDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SiSetModbusCmdDlg(QWidget *parent = 0);
    ~SiSetModbusCmdDlg();

    int getCmdNum();

protected:
    void initWid();

private slots:
    void on_cancelBtn_clicked();

    void on_okBtn_clicked();

private:
    Ui::SiSetModbusCmdDlg *ui;
};

#endif // SISETMODBUSCMDDLG_H
