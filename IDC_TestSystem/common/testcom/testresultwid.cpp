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

    initStytleSheet();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(progressSlot()));
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

void TestResultWid::init(sTestConfigItem *item)
{
    mItem = item;
    QString name = mItem->serialNum.name;
    QString batch = mItem->serialNum.batch;
    QString str = tr("产品:%1  批次：%2").arg(name).arg(batch);
    ui->titleTab->setText(str);
}

void TestResultWid::startSlot()
{
    QString name = mItem->serialNum.name;
    QString batch = mItem->serialNum.batch;
    QString sn = mItem->serialNum.sn;
    mItem->progress.errNum = mItem->progress.finishNum = mItem->progress.okNum = 0;
    mItem->progress.allNum = 3;
    mItem->progress.startTime = QTime::currentTime();

    QString str = tr("产品:%1  批次：%2").arg(name).arg(batch);
    ui->titleTab->setText(str);
    ui->snLab->setText(sn);

    ui->statusLab->setText(tr("正在计算测试项"));
    ui->itemNumLab->setText(tr("已启动测试功能，请等待！！！"));
    ui->progressBar->setValue(0);

    QTimer::singleShot(50*1000,this,SLOT(startTimerSLot()));
    ui->widget->setStyleSheet("QWidget#widget{border-image: url(:/image/resultpix.jpg);border-radius:5px;}"
                              "QWidget{font: 30pt \"微软雅黑\"; color:white;}"
                              "QProgressBar {border:2px solid blue;background-color:transparent;border-radius: 5px;text-align: center;color:white;}" );
    this->setStyleSheet("color:black;");

}

void TestResultWid::startTimerSLot()
{
    timer->start(200);
}

void TestResultWid::resultSlot()
{
    if(!mItem->progress.errNum) {
        ui->widget->setStyleSheet("QWidget#widget{border-image: url(:/image/resultpix.jpg);border-radius:5px;}"
                                  "QWidget{font: 30pt \"微软雅黑\"; color:white;}"
                                  "QProgressBar {border:2px solid blue;background-color:transparent;border-radius: 5px;text-align: center;}");
    } else {
        ui->widget->setStyleSheet("QWidget#widget{border-image: url(:/image/resultpix.jpg);border-radius:5px;}"
                                  "QWidget{font: 30pt \"微软雅黑\"; color:red;}"
                                  "QProgressBar {border:2px solid blue;background-color:transparent;border-radius: 5px;text-align: center;color:white;}"
                                  "QProgressBar::chunk {background-color:red;}");
        this->setStyleSheet("color:red;");
    }

    timer->stop();
    mItem->progress.allNum = mItem->progress.finishNum;
    progressSlot();
    QTime t(0,0,0,0);
    mItem->progress.endTime = QTime::currentTime();
    t = t.addSecs(mItem->progress.startTime.secsTo(mItem->progress.endTime));
    ui->statusLab->setText(tr("测试结束!!! 测试耗时%1").arg(t.toString("hh:mm:ss")));
}

void TestResultWid::progressSlot()
{
    if(Test_Pause == mItem->mode) {
        ui->statusLab->setText(tr("已暂停！！！")); return;
    }
    if(!mItem->progress.errNum) {
        ui->widget->setStyleSheet("QWidget#widget{border-image: url(:/image/resultpix.jpg);border-radius:5px;}"
                                  "QWidget{font: 30pt \"微软雅黑\"; color:white;}"
                                  "QProgressBar {border:2px solid blue;background-color:transparent;border-radius: 5px;text-align: center;}");
    } else {
        ui->widget->setStyleSheet("QWidget#widget{border-image: url(:/image/resultpix.jpg);border-radius:5px;}"
                                  "QWidget{font: 30pt \"微软雅黑\"; color:red;}"
                                  "QProgressBar {border:2px solid blue;background-color:transparent;border-radius: 5px;text-align: center;color:white;}"
                                  "QProgressBar::chunk {background-color:red;}");
        this->setStyleSheet("color:red;");
    }

    sTestProgress *arg = &(mItem->progress);
    int progress = (arg->finishNum * 100.0) / arg->allNum;
    if(progress > 100) return;
    ui->progressBar->setValue(progress);
    ui->statusLab->setText(arg->status);

    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::black);
    if(arg->errNum)  pe.setColor(QPalette::WindowText,Qt::red);

    int ok = (arg->okNum * 100.0) / arg->allNum;
    QString str = tr("测试项目数:%1  失败项目数：%2  项目测试通过率：%3%").arg(arg->allNum).arg(arg->errNum).arg(ok);
    ui->itemNumLab->setText(str);
    ui->itemNumLab->setPalette(pe);
}

