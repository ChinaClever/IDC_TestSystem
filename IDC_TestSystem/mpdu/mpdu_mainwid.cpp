#include "mpdu_mainwid.h"
#include "ui_mpdu_mainwid.h"

MPDU_MainWid::MPDU_MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MPDU_MainWid)
{
    ui->setupUi(this);
     QTimer::singleShot(100,this,SLOT(initFunSLot())); //延时初始化
}

MPDU_MainWid::~MPDU_MainWid()
{
    delete ui;
}


void MPDU_MainWid::initFunSLot()
{
    mtoolBoxWid = new MPDU_ToolBoxWid(ui->toolBoxWid);

    mTestWid = new MpduRtuTest_MainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mTestWid);
}
