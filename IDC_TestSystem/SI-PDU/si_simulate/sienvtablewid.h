#ifndef SIENVTABLEWID_H
#define SIENVTABLEWID_H

#include <QWidget>

namespace Ui {
class SiEnvTableWid;
}

class SiEnvTableWid : public QWidget
{
    Q_OBJECT

public:
    explicit SiEnvTableWid(QWidget *parent = 0);
    ~SiEnvTableWid();

private:
    Ui::SiEnvTableWid *ui;
};

#endif // SIENVTABLEWID_H
