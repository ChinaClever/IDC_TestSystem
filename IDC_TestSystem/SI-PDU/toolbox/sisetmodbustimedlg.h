#ifndef SISETMODBUSTIMEDLG_H
#define SISETMODBUSTIMEDLG_H

#include <QDialog>

namespace Ui {
class SiSetModbusTimeDlg;
}

class SiSetModbusTimeDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SiSetModbusTimeDlg(QWidget *parent = 0);
    ~SiSetModbusTimeDlg();

    int getIndex();
protected:
    void initWid();

private slots:
    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::SiSetModbusTimeDlg *ui;
};

#endif // SISETMODBUSTIMEDLG_H
