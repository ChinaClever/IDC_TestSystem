/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "z_toolboxwid.h"
#include "ui_z_toolboxwid.h"
#include "common.h"

Z_ToolBoxWid::Z_ToolBoxWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Z_ToolBoxWid)
{
    ui->setupUi(this);

    initWid();
    QGridLayout *gridLayout = new QGridLayout(parent);
    gridLayout->setContentsMargins(0, 0, 0, 10);
    gridLayout->addWidget(this);
    groupBox_background_icon(this);
}

Z_ToolBoxWid::~Z_ToolBoxWid()
{
    delete ui;
}


void Z_ToolBoxWid::initWid()
{
    int page = 0;

    mSimulationToolWid = new Z_SimulationToolWid(ui->toolBox->widget(page++));
    connect(mSimulationToolWid, SIGNAL(simulateSig(int)), this, SIGNAL(toolBoxSig(int)));

    mLogsToolWid = new Z_LogsToolWid(ui->toolBox->widget(page++));
    connect(mLogsToolWid, SIGNAL(logsSig(int)), this, SIGNAL(toolBoxSig(int)));

    mSettingToolWid = new Z_SettingToolWid(ui->toolBox->widget(page++));

}

