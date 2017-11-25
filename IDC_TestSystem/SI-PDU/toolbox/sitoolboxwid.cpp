#include "sitoolboxwid.h"
#include "ui_sitoolboxwid.h"

SitoolBoxWid::SitoolBoxWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SitoolBoxWid)
{
    ui->setupUi(this);

    initWid();

}

SitoolBoxWid::~SitoolBoxWid()
{
    delete ui;
}


void SitoolBoxWid::initWid()
{
    int page = 0;

    mSimulationToolWid = new SiSimulationToolWid(ui->toolBox->widget(page++));
    mTestToolWid = new SiTestToolWid(ui->toolBox->widget(page++));
    mSettingToolWid = new SiSettingToolWid(ui->toolBox->widget(page++));
}
