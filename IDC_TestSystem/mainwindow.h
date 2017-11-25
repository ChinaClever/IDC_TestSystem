#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "simainwid.h"

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

private slots:
    void initFunSLot();

    void on_sipduBtn_clicked();

private:
    Ui::MainWindow *ui;

    SIMainWid *mSiWid;
};

#endif // MAINWINDOW_H
