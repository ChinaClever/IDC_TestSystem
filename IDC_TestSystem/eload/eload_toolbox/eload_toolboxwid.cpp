/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "eload_toolboxwid.h"
#include "ui_eload_toolboxwid.h"

ELoad_ToolBoxWid::ELoad_ToolBoxWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ELoad_ToolBoxWid)
{
    ui->setupUi(this);

    initWid();
    QGridLayout *gridLayout = new QGridLayout(parent);
    gridLayout->setContentsMargins(0, 0, 0, 10);
    gridLayout->addWidget(this);
    groupBox_background_icon(this);
}

ELoad_ToolBoxWid::~ELoad_ToolBoxWid()
{
    delete ui;
}


void ELoad_ToolBoxWid::initWid()
{
    int page = 0;

    mHomeToolWid = new ELoad_HomeToolWid(ui->toolBox->widget(page++));
    connect(mHomeToolWid, SIGNAL(toolSig(int)), this, SIGNAL(toolBoxSig(int)));

    mInputToolWid = new ELoad_InputToolWid(ui->toolBox->widget(page++));
    connect(mInputToolWid, SIGNAL(toolSig(int)), this, SIGNAL(toolBoxSig(int)));

    mLogsToolWid = new ELoad_LogsToolWid(ui->toolBox->widget(page++));
    connect(mLogsToolWid, SIGNAL(logsSig(int)), this, SIGNAL(toolBoxSig(int)));

    mSettingToolWid = new ELoad_SettingToolWid(ui->toolBox->widget(page++));
}
