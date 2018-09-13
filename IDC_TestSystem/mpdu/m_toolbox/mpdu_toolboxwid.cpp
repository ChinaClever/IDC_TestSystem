/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "mpdu_toolboxwid.h"
#include "ui_mpdu_toolboxwid.h"
#include "common.h"

MPDU_ToolBoxWid::MPDU_ToolBoxWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MPDU_ToolBoxWid)
{
    ui->setupUi(this);

     initWid();
    QGridLayout *gridLayout = new QGridLayout(parent);
    gridLayout->setContentsMargins(0, 0, 0, 10);
    gridLayout->addWidget(this);
    groupBox_background_icon(this);
}

MPDU_ToolBoxWid::~MPDU_ToolBoxWid()
{
    delete ui;
}


void MPDU_ToolBoxWid::initWid()
{
    int page = 0;

    mModeToolWid = new M_ModeToolWid(ui->toolBox->widget(page++));
    connect(mModeToolWid, SIGNAL(simulateSig(int)), this, SIGNAL(toolBoxSig(int)));

    mStatusToolWid = new M_StatusToolWid(ui->toolBox->widget(page++));
    connect(mStatusToolWid, SIGNAL(widSig(int)), this, SIGNAL(toolBoxSig(int)));

    mLogsToolWid = new M_LogsToolWid(ui->toolBox->widget(page++));
    connect(mLogsToolWid, SIGNAL(logsSig(int)), this, SIGNAL(toolBoxSig(int)));

    mSettingToolWid = new M_SettingToolWid(ui->toolBox->widget(page++));

}
