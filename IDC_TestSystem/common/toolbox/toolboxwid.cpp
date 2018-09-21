#include "toolboxwid.h"
#include "ui_toolboxwid.h"

ToolBoxWid::ToolBoxWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolBoxWid)
{
    ui->setupUi(this);

    mSettingToolWid = nullptr;
    mStatusToolWid = nullptr;
    mLogsToolWid = nullptr;
    mModeToolWid = nullptr;
    mTestToolWid = nullptr;

    QTimer::singleShot(30,this,SLOT(initFunSLot())); //延时初始化
    QGridLayout *gridLayout = new QGridLayout(parent);
    gridLayout->setContentsMargins(0, 0, 0, 10);
    gridLayout->addWidget(this);
    groupBox_background_icon(this);
}

ToolBoxWid::~ToolBoxWid()
{
    delete ui;
}

void ToolBoxWid::initFunSLot()
{
    int page = 0;
    if(mModeToolWid) {
        mModeToolWid->init(mConfig);
        mModeToolWid->setParent(ui->toolBox->widget(page++));
        connect(mModeToolWid, SIGNAL(simulateSig(int)), this, SIGNAL(toolBoxSig(int)));
    }

    if(mStatusToolWid) {
        mStatusToolWid->setParent(ui->toolBox->widget(page++));
        connect(mStatusToolWid, SIGNAL(widSig(int)), this, SIGNAL(toolBoxSig(int)));
    }

    if(mLogsToolWid) {
        mLogsToolWid->init(mConfig);
        mLogsToolWid->setParent(ui->toolBox->widget(page++));
        connect(mLogsToolWid, SIGNAL(logsSig(int)), this, SIGNAL(toolBoxSig(int)));
    }

    if(mSettingToolWid) {
        mSettingToolWid->init(mConfig);
        mSettingToolWid->setParent(ui->toolBox->widget(page++));
    }

    mTestToolWid = new TestToolWid();
    if(mTestToolWid) {
        mTestToolWid->setParent(ui->toolBox->widget(page++));
        connect(mTestToolWid, SIGNAL(simulateSig(int)), this, SIGNAL(toolBoxSig(int)));
    }
}
