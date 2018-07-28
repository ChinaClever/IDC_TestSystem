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

    QGridLayout *gridLayout = new QGridLayout(parent);
    gridLayout->setContentsMargins(0, 0, 0, 10);
    gridLayout->addWidget(this);
    groupBox_background_icon(this);
}

MPDU_ToolBoxWid::~MPDU_ToolBoxWid()
{
    delete ui;
}
