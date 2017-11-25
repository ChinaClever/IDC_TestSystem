#ifndef SITOOLBOXWID_H
#define SITOOLBOXWID_H

#include <QWidget>
#include "sisimulationtoolwid.h"
#include "sitesttoolwid.h"
#include "sisettingtoolwid.h"

namespace Ui {
class SitoolBoxWid;
}

class SitoolBoxWid : public QWidget
{
    Q_OBJECT

public:
    explicit SitoolBoxWid(QWidget *parent = 0);
    ~SitoolBoxWid();

protected:
    void initWid();


private:
    Ui::SitoolBoxWid *ui;

    SiSimulationToolWid *mSimulationToolWid;
    SiTestToolWid *mTestToolWid;
    SiSettingToolWid *mSettingToolWid;
};

#endif // SITOOLBOXWID_H
