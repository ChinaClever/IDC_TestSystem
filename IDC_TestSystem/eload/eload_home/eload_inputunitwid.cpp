/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "eload_inputunitwid.h"
#include "ui_eload_inputunitwid.h"
#include <QGridLayout>
#include <QGraphicsDropShadowEffect>

int gAddr=1,gBit=0,gValue=0;
bool gflag = false;
QMap<int,QLabel *> gQmapRes;
QMap<int,QScrollBar *> gQmapScroll;
QMap<int,bool> gQmapIsSend;
QMap<int,bool> gQmapIsSet;
extern QList<QPair<QPair<int,int>,int>> gListSw;
void setRes(int addr,int bit,int value, bool ret)
{
    gAddr = addr;
    gBit = bit-1;
    gValue = value;
    gflag = ret;
}

ELoad_InputUnitWid::ELoad_InputUnitWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ELoad_InputUnitWid)
{
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(parent);//控制ToolBox自适应
    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->addWidget(this);
//    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
//    shadow->setColor(QColor(248,186,65,150));
//    shadow->setOffset(2,2);
//    shadow->setBlurRadius(1);
//    parent->setGraphicsEffect(shadow);
    QTimer::singleShot(1500,this,SLOT(initFunSLot())); //延时初始化
}

ELoad_InputUnitWid::~ELoad_InputUnitWid()
{
    delete ui;
}


void ELoad_InputUnitWid::initFunSLot()
{
    mRtu = ELoad_RtuSent::bulid();
    mValue = 0;

    timer = new QTimer(this);
    timer->start(1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));

}

void ELoad_InputUnitWid::init(int addr, int bit)
{
    mObjData = &(IN_DataPackets::bulid()->getDev(addr)->data.input[bit]);

    QString str = QString::number((addr-1) * 8 + bit+1);
    QString labstr = ui->label->text()+str;
    ui->label->setText(labstr);
    mAddr = addr;
    mBit = bit;
    gQmapRes.insert(addr*10+bit,ui->resLab);
    gQmapScroll.insert(addr*10+bit,ui->horizontalScrollBar);
    gQmapIsSend.insert(addr*10+bit,false);
    gQmapIsSet.insert(addr*10+bit,false);
    //qDebug()<<addr<<bit<<ui->resLab<<ui->horizontalScrollBar;

    ELoad_ConfigFile *config = ELoad_ConfigFile::bulid();
    int ret = config->getResistance(mAddr,mBit);
    if(ret)
    {
        ui->resLab->setText(QString(tr("%1")).arg(ret));
        ui->horizontalScrollBar->setValue(ret);
    }
    else
    {
        ui->resLab->setText("0");
        ui->horizontalScrollBar->setValue(0);
    }
}

int ELoad_InputUnitWid::getValue()
{
    return ui->horizontalScrollBar->value();
}

void ELoad_InputUnitWid::setValue(int value)
{
    ui->horizontalScrollBar->setValue(value);
}

void ELoad_InputUnitWid::updateWid()
{
    QString str;
    QPalette pe;
    setText(mObjData->vol.value ,mObjData->vol.alarm ,tr(" V") ,ui->volLab ,COM_RATE_VOL);//电压
    setText(mObjData->cur.value ,mObjData->cur.alarm ,tr(" A") ,ui->curLab ,COM_RATE_CUR2);//电流

    str = tr("断开");
    if(mObjData->sw == 1) {
        str = tr("接通");
        pe.setColor(QPalette::WindowText,Qt::black);
    } else {
        pe.setColor(QPalette::WindowText,Qt::red);
    }
    ui->swLab->setText(str);
    ui->swLab->setPalette(pe);

    int addr = -1,bit = -1;
    QList<bool> flag;
    ELoad_RtuSent::bulid()->getValue(addr,bit,flag);
    //if(!flag[addr*8+bit])
    {
        staticSetCurUpdate();
    }
    if(mRtu->mSerial->mSerial->isOpened())
        ui->horizontalScrollBar->setEnabled(true);
    else
        ui->horizontalScrollBar->setEnabled(false);
    //else
    //   autoSetCurUpdate(addr,bit,flag);
}

void ELoad_InputUnitWid::timeoutDone()
{
    updateWid();
}

void ELoad_InputUnitWid::on_openBtn_clicked()
{
    gListSw.append(QPair<QPair<int,int>,int>(QPair<int,int>(mAddr,mBit),1));
    //mRtu->switchOpenCtr(mAddr, mBit);
}

void ELoad_InputUnitWid::on_closeBtn_clicked()
{
   gListSw.append(QPair<QPair<int,int>,int>(QPair<int,int>(mAddr,mBit),0));
   //mRtu->switchCloseCtr(mAddr, mBit);
}

void ELoad_InputUnitWid::on_checkBox_clicked(bool checked)
{
    ui->horizontalScrollBar->setEnabled(!checked);
    if(checked) {
        mRtu->setDpAdjust(mAddr, ELoad_DP_1+mBit, 1000 , 10000, 60000);
    }
    //   else {
    //        mRtu->setData(mAddr, ELoad_DP_1+mBit, 0);
    //    }
}

void ELoad_InputUnitWid::setFunSLot()
{
    if(!gQmapIsSend[mAddr*10+mBit]){
        int value = ui->horizontalScrollBar->value();
        gQmapIsSend[mAddr*10+mBit] = true;
        mRtu->setData(mAddr, ELoad_DP_1+mBit, value);
        //qDebug()<<"eload_inputunitwid.cpp 101th line "<<value;
    }
}

void ELoad_InputUnitWid::on_horizontalScrollBar_sliderMoved(int position)
{
    ui->resLab->setText( QString(tr("%1")).arg(position) );
}

void ELoad_InputUnitWid::setText(ushort value , ushort alarm,QString text,QLabel* lab,double rate)
{
    QString str;
    QPalette pe;
    if(value){
        double valuetext = value / rate;
        str = QString::number(valuetext) + text;
        lab->setText(str);
        if(alarm) {
            pe.setColor(QPalette::WindowText,Qt::red);
        } else {
            pe.setColor(QPalette::WindowText,Qt::black);
        }
        lab->setPalette(pe);
    }else{
        QString str = QString::number(0) + text;
        lab->setText(str);
        pe.setColor(QPalette::WindowText,Qt::black);
        lab->setPalette(pe);
    }
}

void ELoad_InputUnitWid::on_horizontalScrollBar_sliderReleased()
{
    if(!gQmapIsSet[mAddr*10+mBit]) {
        gQmapIsSet[mAddr*10+mBit] = true;
        QTimer::singleShot(3*1000,this,SLOT(setFunSLot())); //延时初始化
        ui->horizontalScrollBar->setEnabled(false);
    }
}

void ELoad_InputUnitWid::staticSetCurUpdate()
{
    if(gQmapIsSet[mAddr*10+mBit]&&gQmapIsSend[mAddr*10+mBit]){
        ELoad_ConfigFile *config = ELoad_ConfigFile::bulid();
        if(!gflag && gValue == 1){//更改阻值失败
            int oldValue = config->getResistance(mAddr,mBit);
            //qDebug()<<"fail"<<mAddr<<mBit<<gQmapRes[mAddr*10+mBit]<<gQmapScroll[mAddr*10+mBit]<<oldValue;
            if(gQmapRes[mAddr*10+mBit]&&gQmapScroll[mAddr*10+mBit]){
                if(oldValue){
                    gQmapRes[mAddr*10+mBit]->setText(QString(tr("%1")).arg(oldValue));
                    gQmapScroll[mAddr*10+mBit]->setValue(oldValue);
                    gQmapScroll[mAddr*10+mBit]->setEnabled(true);
                }
                else{
                    gQmapRes[mAddr*10+mBit]->setText("0");
                    gQmapScroll[mAddr*10+mBit]->setValue(0);
                    gQmapScroll[mAddr*10+mBit]->setEnabled(true);
                }

                gQmapIsSet[mAddr*10+mBit] = false;
                gQmapIsSend[mAddr*10+mBit] = false;
                gValue = 0;
            }
        }
        else if(gflag){//更改阻值成功
            //qDebug()<<"success"<<gQmapRes[gAddr*10+gBit]<<gQmapScroll[gAddr*10+gBit]<<gValue;
            if(gQmapRes[gAddr*10+gBit] && gQmapScroll[gAddr*10+gBit]){
                config->setResistance(gAddr,gBit,gValue);
                gQmapRes[gAddr*10+gBit]->setText( QString(tr("%1")).arg(gValue) );
                gQmapScroll[gAddr*10+gBit]->setValue(gValue);
                gQmapScroll[gAddr*10+gBit]->setEnabled(true);

                gQmapIsSet[mAddr*10+mBit] = false;
                gQmapIsSend[mAddr*10+mBit] = false;
                gValue = 0;gflag = false;
            }
        }
    }
}

void ELoad_InputUnitWid::autoSetCurUpdate(int addr , int bit , QList<bool> flag)
{
    ELoad_ConfigFile *config = ELoad_ConfigFile::bulid();

    if(gflag){//更改阻值成功
        //qDebug()<<"auto success"<<gQmapRes[gAddr*10+gBit]<<gQmapScroll[gAddr*10+gBit]<<gValue;
        if(gQmapRes[gAddr*10+gBit] && gQmapScroll[gAddr*10+gBit]){
            config->setResistance(gAddr,gBit,gValue);
            gQmapRes[gAddr*10+gBit]->setText( QString(tr("%1")).arg(gValue) );
            gQmapScroll[gAddr*10+gBit]->setValue(gValue);
            gQmapScroll[gAddr*10+gBit]->setEnabled(true);

            flag[gAddr*8+gBit] = false;gValue = 0;gflag = false;
            ELoad_RtuSent::bulid()->setValue(gAddr , gBit, flag);
        }
    }
    else{
        static int count = 0;
        if(!gflag && gValue == 1){//更改阻值失败
            if(count < 2){
                count ++;
                return;
            }
            int oldValue = config->getResistance(addr,bit);
            //qDebug()<<"auto fail"<<mAddr<<mBit<<gQmapRes[mAddr*10+mBit]<<gQmapScroll[mAddr*10+mBit]<<oldValue;
            if(gQmapRes[addr*10+bit]&&gQmapScroll[addr*10+bit]){
                if(oldValue){
                    gQmapRes[addr*10+bit]->setText(QString(tr("%1")).arg(oldValue));
                    gQmapScroll[addr*10+bit]->setValue(oldValue);
                    gQmapScroll[addr*10+bit]->setEnabled(true);
                }
                else{
                    gQmapRes[addr*10+bit]->setText("0");
                    gQmapScroll[addr*10+bit]->setValue(0);
                    gQmapScroll[addr*10+bit]->setEnabled(true);
                }

                flag[addr*8+bit] = false;gValue = 0;count = 0;
                ELoad_RtuSent::bulid()->setValue(addr , bit, flag);
            }
        }
    }
}

void ELoad_InputUnitWid::setResistance(int id , int value)
{
    mAddr = (id-1)/ 8 + 1;
    mBit = (id-1) % 8;
    mValue = value;
    if(mRtu->mSerial->mSerial->isOpened())
    {
        if(!gQmapIsSet[mAddr*10+mBit]) {
        gQmapIsSet[mAddr*10+mBit] = true;
        QTimer::singleShot(3*1000,this,SLOT(setResSLot())); //延时初始化
        gQmapScroll[mAddr*10+mBit]->setEnabled(false);
        }
    }
}

void ELoad_InputUnitWid::setResSLot()
{
    if(!gQmapIsSend[mAddr*10+mBit]){
        int value = mValue;
        gQmapIsSend[mAddr*10+mBit] = true;
        mRtu->setData(mAddr, ELoad_DP_1+mBit, value);
        gQmapRes[mAddr*10+mBit]->setText( QString(tr("%1")).arg(value) );
        gQmapScroll[mAddr*10+mBit]->setValue(value);
    }
}
