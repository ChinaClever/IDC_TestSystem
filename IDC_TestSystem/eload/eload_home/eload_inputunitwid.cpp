/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "eload_inputunitwid.h"
#include "ui_eload_inputunitwid.h"

int gAddr=1,gBit=0,gValue=0;
bool gflag = false;
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
    gridLayout->addWidget(this);
    QTimer::singleShot(1500,this,SLOT(initFunSLot())); //延时初始化
}

ELoad_InputUnitWid::~ELoad_InputUnitWid()
{
    delete ui;
}


void ELoad_InputUnitWid::initFunSLot()
{
    mRtu = ELoad_RtuSent::bulid();

    timer = new QTimer(this);
    timer->start(1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));

}

void ELoad_InputUnitWid::init(int addr, int bit)
{
    mObjData = &(IN_DataPackets::bulid()->getDev(addr)->data.input[bit]);
    QString str = QString::number((addr-1) * 8 + bit+1);
    ui->inputLab->setText(tr(""));
    QString labstr = ui->label->text()+str;
    ui->label->setText(labstr);
    mAddr = addr;
    mBit = bit;
    mQmapRes.insert(addr*10+bit,ui->resLab);
    mQmapScroll.insert(addr*10+bit,ui->horizontalScrollBar);
    mQmapIsSend.insert(addr*10+bit,false);
    mQmapIsSet.insert(addr*10+bit,false);
    //qDebug()<<addr<<bit<<ui->resLab<<ui->horizontalScrollBar;

    ELoad_ConfigFile *config = ELoad_ConfigFile::bulid();
    int ret = config->getResistance(mAddr,mBit);
    if(ret)
    {
        ui->resLab->setText(QString(tr("%1Ω")).arg(ret));
        ui->horizontalScrollBar->setValue(ret);
    }
    else
    {
        ui->resLab->setText("0Ω");
        ui->horizontalScrollBar->setValue(0);
    }
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

    //int addr = -1,bit = -1;
    //QList<bool> flag;
    //ELoad_RtuSent::bulid()->getValue(addr,bit,flag);
    //if(!flag[addr*8+bit])
        staticSetCurUpdate();
    //else
    //    autoSetCurUpdate(addr,bit,flag);
}

void ELoad_InputUnitWid::timeoutDone()
{
    updateWid();
}

void ELoad_InputUnitWid::on_openBtn_clicked()
{
    mRtu->switchOpenCtr(mAddr, mBit);
}

void ELoad_InputUnitWid::on_closeBtn_clicked()
{
    mRtu->switchCloseCtr(mAddr, mBit);
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
    if(!mQmapIsSend[mAddr*10+mBit]){
    int value = ui->horizontalScrollBar->value();
    mQmapIsSend[mAddr*10+mBit] = true;
    mRtu->setData(mAddr, ELoad_DP_1+mBit, value);
    qDebug()<<"eload_inputunitwid.cpp 101th line "<<value;
    }
}

void ELoad_InputUnitWid::on_horizontalScrollBar_sliderMoved(int position)
{
    ui->resLab->setText( QString(tr("%1Ω")).arg(position) );
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
    if(!mQmapIsSet[mAddr*10+mBit]) {
        mQmapIsSet[mAddr*10+mBit] = true;
        QTimer::singleShot(5*1000,this,SLOT(setFunSLot())); //延时初始化
        ui->horizontalScrollBar->setEnabled(false);
    }
}

void ELoad_InputUnitWid::staticSetCurUpdate()
{
    if((mQmapIsSet[mAddr*10+mBit]&&mQmapIsSend[mAddr*10+mBit])
            || (gAddr != -1 && gBit != -1 && mQmapIsSet[gAddr*10+gBit] && mQmapIsSend[gAddr*10+gBit])){
        ELoad_ConfigFile *config = ELoad_ConfigFile::bulid();
        if(!gflag && gValue == 1){//更改阻值失败
            int oldValue = config->getResistance(mAddr,mBit);
            //qDebug()<<"fail"<<mAddr<<mBit<<mQmapRes[mAddr*10+mBit]<<mQmapScroll[mAddr*10+mBit]<<oldValue;
            if(mQmapRes[mAddr*10+mBit]&&mQmapScroll[mAddr*10+mBit]){
                if(oldValue){
                    mQmapRes[mAddr*10+mBit]->setText(QString(tr("%1Ω")).arg(oldValue));
                    mQmapScroll[mAddr*10+mBit]->setValue(oldValue);
                    mQmapScroll[mAddr*10+mBit]->setEnabled(true);
                }
                else{
                    mQmapRes[mAddr*10+mBit]->setText("0Ω");
                    mQmapScroll[mAddr*10+mBit]->setValue(0);
                    mQmapScroll[mAddr*10+mBit]->setEnabled(true);
                }

                mQmapIsSet[mAddr*10+mBit] = false;
                mQmapIsSend[mAddr*10+mBit] = false;
                gValue = 0;
            }
        }
        else if(gflag && gAddr != -1 && gBit != -1){//更改阻值成功
            //qDebug()<<"success"<<mQmapRes[gAddr*10+gBit]<<mQmapScroll[gAddr*10+gBit]<<gValue;
            if(mQmapRes[gAddr*10+gBit] && mQmapScroll[gAddr*10+gBit]){
                config->setResistance(gAddr,gBit,gValue);
                mQmapRes[gAddr*10+gBit]->setText( QString(tr("%1Ω")).arg(gValue) );
                mQmapScroll[gAddr*10+gBit]->setValue(gValue);
                mQmapScroll[gAddr*10+gBit]->setEnabled(true);

                mQmapIsSet[mAddr*10+mBit] = false;
                mQmapIsSend[mAddr*10+mBit] = false;
                gValue = 0;gAddr = -1;gBit = -1;gflag = false;
            }
        }
    }
}

void ELoad_InputUnitWid::autoSetCurUpdate(int addr , int bit , QList<bool> flag)
{
    ELoad_ConfigFile *config = ELoad_ConfigFile::bulid();

    if(gflag && gAddr != -1 && gBit != -1){//更改阻值成功
        //qDebug()<<"auto success"<<mQmapRes[gAddr*10+gBit]<<mQmapScroll[gAddr*10+gBit]<<gValue;
        if(mQmapRes[gAddr*10+gBit] && mQmapScroll[gAddr*10+gBit]){
            config->setResistance(gAddr,gBit,gValue);
            mQmapRes[gAddr*10+gBit]->setText( QString(tr("%1Ω")).arg(gValue) );
            mQmapScroll[gAddr*10+gBit]->setValue(gValue);
            mQmapScroll[gAddr*10+gBit]->setEnabled(true);

            flag[gAddr*8+gBit] = false;gValue = 0;gAddr = -1;gBit = -1;gflag = false;
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
            //qDebug()<<"auto fail"<<mAddr<<mBit<<mQmapRes[mAddr*10+mBit]<<mQmapScroll[mAddr*10+mBit]<<oldValue;
            if(mQmapRes[addr*10+bit]&&mQmapScroll[addr*10+bit]){
                if(oldValue){
                    mQmapRes[addr*10+bit]->setText(QString(tr("%1Ω")).arg(oldValue));
                    mQmapScroll[addr*10+bit]->setValue(oldValue);
                    mQmapScroll[addr*10+bit]->setEnabled(true);
                }
                else{
                    mQmapRes[addr*10+bit]->setText("0Ω");
                    mQmapScroll[addr*10+bit]->setValue(0);
                    mQmapScroll[addr*10+bit]->setEnabled(true);
                }

                flag[addr*8+bit] = false;gValue = 0;count = 0;addr = -1;bit = -1;
                ELoad_RtuSent::bulid()->setValue(addr , bit, flag);
            }
        }
    }
}
