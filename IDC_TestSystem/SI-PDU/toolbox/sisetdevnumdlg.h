#ifndef SISETDEVNUMDLG_H
#define SISETDEVNUMDLG_H

#include <QDialog>

namespace Ui {
class SiSetDevNumDlg;
}

class SiSetDevNumDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SiSetDevNumDlg(QWidget *parent = 0);
    ~SiSetDevNumDlg();

    int getNum();

protected:
    void initWid();

private slots:
    void on_cancelBtn_clicked();

    void on_okBtn_clicked();

private:
    Ui::SiSetDevNumDlg *ui;
};

#endif // SISETDEVNUMDLG_H
