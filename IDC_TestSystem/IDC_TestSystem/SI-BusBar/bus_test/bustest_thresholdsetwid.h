#ifndef BUSTEST_THRESHOLDSETWID_H
#define BUSTEST_THRESHOLDSETWID_H

#include <QWidget>

namespace Ui {
class BUSTEST_ThresholdSetWid;
}

class BUSTEST_ThresholdSetWid : public QWidget
{
    Q_OBJECT

public:
    explicit BUSTEST_ThresholdSetWid(QWidget *parent = 0);
    ~BUSTEST_ThresholdSetWid();
    void initWidget();
    void sendCmd();
    int mAddr;
    int mBus;
    int mId;
signals:
    void updateAddr(int);
    void updateBus(int);

private slots:
    void on_updateBtn_clicked();
    void on_setBtn_clicked();
    void on_busBox_currentIndexChanged(int index);
    void on_addrBox_currentIndexChanged(int index);
    void on_lineBox_currentIndexChanged(int index);

private:
    Ui::BUSTEST_ThresholdSetWid *ui;
};

#endif // BUSTEST_THRESHOLDSETWID_H
