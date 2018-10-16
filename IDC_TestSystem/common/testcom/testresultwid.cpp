/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "testresultwid.h"
#include "ui_testresultwid.h"
#include <QGraphicsDropShadowEffect>
TestResultWid::TestResultWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestResultWid)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(progressSlot()));


   initStytleSheet();
}

TestResultWid::~TestResultWid()
{
    delete ui;
}

void TestResultWid::initStytleSheet()
{
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setColor(Qt::darkGray);
    shadow->setOffset(5,5);
    shadow->setBlurRadius(30);
    QGraphicsDropShadowEffect *shadow1 = new QGraphicsDropShadowEffect(this);
    shadow1->setColor(Qt::darkGray);
    shadow1->setOffset(5,5);
    shadow1->setBlurRadius(30);
    ui->widget_3->setGraphicsEffect(shadow);
    ui->widget->setGraphicsEffect(shadow1);
    set_background_icon(this,":/image/box_back.jpg");
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

    timer->start(200);
    ui->widget->setStyleSheet("QWidget#widget{border-image: url(:/image/run.jpg);border-radius:5px;}"
                              "QWidget{font: 20pt \"微软雅黑\"; color:white;}"
                              "QProgressBar {border:2px solid blue;background-color:transparent;border-radius: 5px;text-align: center;}" );
    this->setStyleSheet("color:black;");

}

void TestResultWid::resultSlot()
{
    bool p = true;
    if(mItem->progress.errNum)  p = false;

    //QString str = tr("通过");
    if(p) {
        ui->widget->setStyleSheet("QWidget#widget{border-image: url(:/image/pass.jpg);border-radius:5px;"
                                  "QWidget{font: 20pt \"微软雅黑\"; color:white;}"
                                  "QProgressBar {border:2px solid blue;background-color:transparent;border-radius: 5px;text-align: center;}}");
    } else {
        //str = tr("失败");
        ui->widget->setStyleSheet("QWidget#widget{border-image: url(:/image/fail.jpg);border-radius:5px;}"
                                  "QWidget{font: 20pt \"微软雅黑\"; color:white;}"
                                  "QProgressBar {border:2px solid blue;background-color:transparent;border-radius: 5px;text-align: center;}");
        this->setStyleSheet("color:red;");
    }

    timer->stop();
    //ui->resultLab->setText(str);

    mItem->progress.allNum = mItem->progress.finishNum;
    progressSlot();
    ui->statusLab->setText(tr("测试结束!!!"));
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

}

