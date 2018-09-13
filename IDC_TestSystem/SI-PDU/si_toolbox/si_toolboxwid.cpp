#include "si_toolboxwid.h"
#include "ui_si_toolboxwid.h"

SI_ToolBoxWid::SI_ToolBoxWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SI_ToolBoxWid)
{
    ui->setupUi(this);
    initWid();
}

SI_ToolBoxWid::~SI_ToolBoxWid()
{
    delete ui;
}


void SI_ToolBoxWid::initWid()
{
    int page = 0;

    mModeToolWid = new SI_ModeToolWid(ui->toolBox->widget(page++));
    connect(mModeToolWid, SIGNAL(simulateSig(int)), this, SIGNAL(toolBoxSig(int)));

    mStatusToolWid = new SI_StatusToolWid(ui->toolBox->widget(page++));
    connect(mStatusToolWid, SIGNAL(widSig(int)), this, SIGNAL(toolBoxSig(int)));

    mLogsToolWid = new SI_LogsToolWid(ui->toolBox->widget(page++));
    connect(mLogsToolWid, SIGNAL(logsSig(int)), this, SIGNAL(toolBoxSig(int)));

    mSettingToolWid = new SI_SettingToolWid(ui->toolBox->widget(page++));

}
