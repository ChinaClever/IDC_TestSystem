#ifndef SILOGSTIMETOOLDLG_H
#define SILOGSTIMETOOLDLG_H

#include <QDialog>

namespace Ui {
class SiLogsTimeToolDlg;
}

class SiLogsTimeToolDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SiLogsTimeToolDlg(QWidget *parent = 0);
    ~SiLogsTimeToolDlg();

    int getTime();

protected:
    void initWid();

private slots:
    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::SiLogsTimeToolDlg *ui;
};

#endif // SILOGSTIMETOOLDLG_H
