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

    mModeToolWid = new Z_ModeToolWid(ui->toolBox->widget(page++));
    connect(mModeToolWid, SIGNAL(simulateSig(int)), this, SIGNAL(toolBoxSig(int)));

    mStatusToolWid = new Z_StatusToolWid(ui->toolBox->widget(page++));
    connect(mStatusToolWid, SIGNAL(widSig(int)), this, SIGNAL(toolBoxSig(int)));

    mLogsToolWid = new Z_LogsToolWid(ui->toolBox->widget(page++));
    connect(mLogsToolWid, SIGNAL(logsSig(int)), this, SIGNAL(toolBoxSig(int)));

    mSettingToolWid = new Z_SettingToolWid(ui->toolBox->widget(page++));

}

