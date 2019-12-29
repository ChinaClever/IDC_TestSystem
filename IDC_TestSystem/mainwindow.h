#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "simainwid.h"
#include "bus_mainwid.h"
#include "mpdu_mainwid.h"
#include "zpdu_mainwid.h"
#include "ip_mainwid.h"
#include "eload_mainwid.h"
#include "rpdu_mainwid.h"
#include "mpduv1_mainwid.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void initWid();

private:
    void setButtonColor(QPushButton *button);

private slots:
    void initFunSLot();
    void on_sipduBtn_clicked();
    void on_siBusBtn_clicked();
    void on_mpduBtn_clicked();
    void on_ippduBtn_clicked();
    void on_zpduBtn_clicked();
    void on_eloadBtn_clicked();
    void on_rpduBtn_clicked();
    void on_mpduv1Btn_clicked();

private:
    Ui::MainWindow *ui;

    SIMainWid *mSiWid;
    BUS_MainWid *mBusWid;
    MPDU_MainWid *mMpduWid;
    ZPDU_MainWid *mZpduWid;
    IP_MainWid *mIpWid;
    ELoad_MainWid *mELoadWid;
    RPDU_MainWid *mRpduWid;
    MPDUV1_MainWid *mMpduV1Wid;
};

#endif // MAINWINDOW_H
