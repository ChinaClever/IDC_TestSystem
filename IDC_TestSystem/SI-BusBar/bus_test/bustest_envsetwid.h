#ifndef BUSTEST_ENVSETWID_H
#define BUSTEST_ENVSETWID_H

#include <QWidget>

namespace Ui {
class BUSTEST_EnvSetWid;
}

class BUSTEST_EnvSetWid : public QWidget
{
    Q_OBJECT

public:
    explicit BUSTEST_EnvSetWid(QWidget *parent = 0);
    ~BUSTEST_EnvSetWid();
    int mAddr;
    int mBus;
    void updateAddr(int);
    void updateBus(int);
    void initWidget();
    void sendCmd();
    ushort change(int index);

private slots:
    void on_updateBtn_clicked();
    void on_setBtn_clicked();
    void on_changeEnvBtn_clicked();
    void on_changeAddrBtn_clicked();
    void on_changeBaudBtn_clicked();
    void on_envBox_currentIndexChanged(int index);

private:
    Ui::BUSTEST_EnvSetWid *ui;
};

#endif // BUSTEST_ENVSETWID_H
