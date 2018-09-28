/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "testresultwid.h"
#include "ui_testresultwid.h"

TestResultWid::TestResultWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestResultWid)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(progressSlot()));
}

TestResultWid::~TestResultWid()
{
    delete ui;
}

void TestResultWid::startSlot()
{
    QString name = mItem->serialNum.name;
    QString batch = mItem->serialNum.batch;
    QString sn = mItem->serialNum.sn;
    mItem->progress.errNum = mItem->progress.finishNum = mItem->progress.okNum = 0;

    QString str = tr("产品:%1  批次：%2").arg(name).arg(batch);
    ui->titleTab->setText(str);
    ui->snLab->setText(sn);

    ui->itemNumLab->clear();
    ui->statusLab->clear();
    ui->progressBar->setValue(0);

    timer->start(1*1000);
    this->setStyleSheet("color:black;");
}

void TestResultWid::resultSlot()
{
    bool p = true;
    if(mItem->progress.errNum)  p = false;

    QString str = tr("通过");
    if(p) {

    } else {
        str = tr("失败");
        this->setStyleSheet("color:red;");
    }

    timer->stop();
    ui->resultLab->setText(str);
}

void TestResultWid::progressSlot()
{
    sTestProgress *arg = &(mItem->progress);

    int progress = (arg->finishNum * 100.0) / arg->allNum;
    ui->progressBar->setValue(progress);
    ui->statusLab->setText(arg->status);

    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::black);
    int ok = (arg->okNum * 100.0) / arg->allNum;
    if(arg->errNum)  pe.setColor(QPalette::WindowText,Qt::red);
    QString str = tr("测试项目数:%1  失败项目数：%2  项目测试通过率：%3%").arg(arg->allNum).arg(arg->errNum).arg(ok);
    ui->itemNumLab->setText(str);
    ui->itemNumLab->setPalette(pe);

    if(progress >= 100) {
        resultSlot();
    }
}

