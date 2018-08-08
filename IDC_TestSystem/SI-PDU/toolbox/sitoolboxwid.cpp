/*
 * Si toolBox
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "sitoolboxwid.h"
#include "ui_sitoolboxwid.h"

SitoolBoxWid::SitoolBoxWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SitoolBoxWid)
{
    ui->setupUi(this);

    initWid();

    QGridLayout *gridLayout = new QGridLayout(parent);
    gridLayout->setContentsMargins(0, 0, 0, 10);
    gridLayout->addWidget(this);
    groupBox_background_icon(this);
//    btnBlue_style_sheet(this);
}

SitoolBoxWid::~SitoolBoxWid()
{
    delete ui;
}


void SitoolBoxWid::initWid()
{
    int page = 0;

    mSimulationToolWid = new SiSimulationToolWid(ui->toolBox->widget(page++));
    connect(mSimulationToolWid, SIGNAL(simulateSig(int)), this, SIGNAL(toolBoxSig(int)));

    mLogsToolWid = new SiLogsToolWid(ui->toolBox->widget(page++));
    connect(mLogsToolWid, SIGNAL(logsSig(int)), this, SIGNAL(toolBoxSig(int)));

    mTestToolWid = new SiTestToolWid(ui->toolBox->widget(page++));
    mSettingToolWid = new SiSettingToolWid(ui->toolBox->widget(page++));
}
