#include "ztest_mainwid.h"
#include "ui_ztest_mainwid.h"
#include "z_testsw/ztest_swwid.h"

ZTest_MainWid::ZTest_MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZTest_MainWid)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
    QTimer::singleShot(600,this,SLOT(initFunSLot()));
}

ZTest_MainWid::~ZTest_MainWid()
{
    delete ui;
}


void ZTest_MainWid::initFunSLot()
{
    ZTest_SwWid *swWid = new ZTest_SwWid(ui->tabWidget);
    ui->tabWidget->addTab(swWid, tr("输出位开关"));

}
