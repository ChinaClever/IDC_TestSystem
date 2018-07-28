/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "ip_toolboxwid.h"
#include "ui_ip_toolboxwid.h"
#include <QGridLayout>

IP_ToolBoxWid::IP_ToolBoxWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IP_ToolBoxWid)
{
    ui->setupUi(this);

    initWid();
    QGridLayout *gridLayout = new QGridLayout(parent);
    gridLayout->setContentsMargins(0, 0, 0, 10);
    gridLayout->addWidget(this);
    groupBox_background_icon(this);
}

IP_ToolBoxWid::~IP_ToolBoxWid()
{
    delete ui;
}


void IP_ToolBoxWid::initWid()
{
    int page = 0;

    mSimulationToolWid = new IP_SimulationToolWid(ui->toolBox->widget(page++));
    connect(mSimulationToolWid, SIGNAL(simulateSig(int)), this, SIGNAL(toolBoxSig(int)));

    mLogsToolWid = new IP_LogsToolWid(ui->toolBox->widget(page++));
    connect(mLogsToolWid, SIGNAL(logsSig(int)), this, SIGNAL(toolBoxSig(int)));

    mSettingToolWid = new IP_SettingToolWid(ui->toolBox->widget(page++));

}
