#ifndef SISETLINENUM_H
#define SISETLINENUM_H

#include <QDialog>

namespace Ui {
class SiSetLineNum;
}

class SiSetLineNum : public QDialog
{
    Q_OBJECT

public:
    explicit SiSetLineNum(QWidget *parent = 0);
    ~SiSetLineNum();

    int getLineNum();

protected:
    void initWid();

private slots:
    void on_cancelBtn_clicked();

    void on_okBtn_clicked();

private:
    Ui::SiSetLineNum *ui;
};

#endif // SISETLINENUM_H
