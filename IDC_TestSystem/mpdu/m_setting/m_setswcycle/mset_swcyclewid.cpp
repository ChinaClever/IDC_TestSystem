#include "mset_swcyclewid.h"
#include "ui_mset_swcyclewid.h"
MSet_SwCycleWid::MSet_SwCycleWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MSet_SwCycleWid)
{
    ui->setupUi(this);
    mReg = 1003;//MPDU首位输出位寄存器地址
    initwid();
}

MSet_SwCycleWid::~MSet_SwCycleWid()
{
    delete ui;
}

void MSet_SwCycleWid::initwid()
{
    QWidget *wid[] = {ui->widget_1, ui->widget_2, ui->widget_3, ui->widget_4, ui->widget_5,ui->widget_6,
                      ui->widget_7, ui->widget_8, ui->widget_9, ui->widget_10, ui->widget_11, ui->widget_12,
                      ui->widget_13,ui->widget_14, ui->widget_15, ui->widget_16,ui->widget_17,ui->widget_18,
                      ui->widget_19,ui->widget_20,ui->widget_21,ui->widget_22,ui->widget_23,ui->widget_24};

    for(int i=0; i<24; ++i) {
        mWid[i] = new MSet_SwCycleItemWid(wid[i]);//24个输出位控件QWidget
        mWid[i]->init(i);
    }

    mTimer =new QTimer(this);
    connect(mTimer,SIGNAL(timeout()),this,SLOT(updateSlot()));

    mCaseCount = 0;
    mCycleCount = 0;

    mSnmp = new MSet_SnmpThread(this);
    connect(mSnmp, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));

    mRtu = new MSet_RtuThread(this);
    mRtu->mReg = mReg;
    connect(mRtu, SIGNAL(cmdSig(QString)), this, SLOT(updateTextSlot(QString)));
}

/**
 * @brief 更新textEdit打印信息
 * @param [in] str 打印信息字符串
 */
void MSet_SwCycleWid::updateTextSlot(QString str)
{
    ui->textEdit->append(str);
}

void MSet_SwCycleWid::on_checkBox_clicked(bool checked)
{
    for(int i=0; i<24; ++i) {
        mWid[i]->setSelect(checked);
    }
}

/**
 * @brief 选择连续和不选择的状态切换时，更新循环次数和情况次数
 * @param [in]checked 选择连续true ，不选择连续false
 */
void MSet_SwCycleWid::on_radioButton_clicked(bool checked)
{
    if(checked)
    {
        ui->cycleCountpinBox->setEnabled(false);
        ui->label_3->setEnabled(false);
    }
    else
    {
        ui->cycleCountpinBox->setEnabled(true);
        ui->label_3->setEnabled(true);
    }
    mCaseCount = 0;
    mCycleCount = 0;
    QString str = QString(tr("当前次数：%1次")).arg(mCycleCount);
    ui->cycleCountlab->setText(str);
}

/**
 * @brief 获取输出位序号的SNMP 对应Oid节点
 * @param [in]i [0,23]选择的输出位序号
 * @return oid 对应Oid节点
 */
QString MSet_SwCycleWid::getOid(int i)
{
    QString oid = QString("%1.%2.%3.7.%4.0")
            .arg(MIB_OID_CLEVER)
            .arg(M_MIB_OID)
            .arg(ui->spinBox->value())
            .arg(i+1);
    return oid;
}

/**
 * @brief SNMP 命令加入命令链表 第一种情况：把第一个选择的输出位ON，其它的输出位OFF
 * @param [in&out]mtimers 只能是0，选择输出位的最小序号
 */
void MSet_SwCycleWid::snmpFirstCase(int& mtimers)
{
    for(int i = mtimers ; i < mSelect.size() ; ++i)
     {
        sSnmpSetCmd cmd;

        cmd.oid = getOid(mSelect[i]);
        cmd.type = SNMP_STRING_TYPE;
        cmd.value.append( i == 0 ? "ON" : "OFF" );
        mSnmp->setCmd(cmd);
    }
}

/**
 * @brief SNMP 命令加入命令链表 其他情况一 end(true)：前一个的输出位OFF，后一个的输出位ON
 * @brief 其他情况二 end(false)：最后一个的输出位OFF
 * @param [in&out]mtimers [1,23]，输出位的序号
 * @param [in]end 其他一般情况true ，灭掉最后一个输出位false
 */
void MSet_SwCycleWid::snmpOtherCase(int& mtimers ,bool end)
{
    sSnmpSetCmd cmd;

    cmd.oid = getOid(mSelect[mtimers-1]);
    cmd.type = SNMP_STRING_TYPE;
    cmd.value.append("OFF");
    mSnmp->setCmd(cmd);
    if(end)
    {
        sSnmpSetCmd cmd1;
        cmd1.oid = getOid(mSelect[mtimers]);
        cmd1.type = SNMP_STRING_TYPE;
        cmd1.value.append("ON");
        mSnmp->setCmd(cmd1);
    }
}

/**
 * @brief 启动线程发送snmp命令
 * @param [in&out]mtimers [0,23]输出位的序号
 */
void MSet_SwCycleWid::sendSnmp(int& mtimers)
{
    if(mtimers == mSelect.size())
    {
        snmpOtherCase(mtimers , false);
        mSnmp->start();
        updateCycleCount();
        return;
    }
    (mtimers == 0)? snmpFirstCase(mtimers): snmpOtherCase(mtimers , true);
    mCaseCount++;
    mSnmp->start();

    ui->textEdit->clear();
}

/**
 * @brief Rtu 命令加入命令链表 第一种情况：把第一个选择的输出位ON
 * @param [in&out]mtimers 只能是0，选择输出位的最小序号
 */
void MSet_SwCycleWid::rtuFirstCase(int& mtimers)
{

    sRtuSetCmd cmd;
    cmd.addr = ui->spinBox->value();
    cmd.reg = mReg + mtimers;
    cmd.value = 1;
    mRtu->setCmd(cmd);
}

/**
 * @brief Rtu 命令加入命令链表 其他情况一 end(true)：前一个的输出位OFF，后一个的输出位ON
 * @brief 其他情况二 end(false)：最后一个的输出位OFF
 * @param [in&out]mtimers [1,23]，输出位的序号
 *  @param [in]end 其他一般情况true ，灭掉最后一个输出位false
 */
void MSet_SwCycleWid::rtuOtherCase(int& mtimers ,bool end)
{
    sRtuSetCmd cmd;
    cmd.addr = ui->spinBox->value();
    cmd.reg = mReg + mSelect[mtimers - 1];
    cmd.value = 0;
    mRtu->setCmd(cmd);
    if(end)
    {
        sRtuSetCmd cmd1;
        cmd1.addr = ui->spinBox->value();
        cmd1.reg = mReg + mSelect[mtimers];
        cmd1.value = 1;
        mRtu->setCmd(cmd1);
    }
}

/**
 * @brief 启动线程发送Rtu命令
 * @param [in&out]mtimers [0,23]输出位的序号
 */
void MSet_SwCycleWid::sendRtu(int& mtimers)
{
    if(mtimers == mSelect.size())
    {
        rtuOtherCase(mtimers , false);
        mRtu->start();
        updateCycleCount();
        return;
    }
    (mtimers == 0)? rtuFirstCase(mtimers): rtuOtherCase(mtimers , true);
    mCaseCount++;
    mRtu->start();

    ui->textEdit->clear();
}

/**
 * @brief 产生命令，并且启动线程发送命令
 * @param [in&out]mtimers [0,23]输出位的序号
 */
void MSet_SwCycleWid::produceCmd(int& mtimers)
{
    sConfigItem *item = M_ConfigFile::bulid()->item;
    if(item->setMode == Test_SNMP)
    {
        sendSnmp(mtimers);
    }
    else
    {
        sendRtu(mtimers);
    }
}

/**
 * @brief 计时器槽函数，时间到则发送对应情况的命令
 */
void MSet_SwCycleWid::updateSlot()
{
    produceCmd(mCaseCount);
}

void MSet_SwCycleWid::on_startBtn_clicked()
{
    mSelect.clear();
    for(int i=0; i<24; ++i) {
        if(mWid[i]->select()) {
            mSelect.append(i);
        }
    }

    mCaseCount = 0;//每次启动时更新循环次数状态
    mCycleCount = 0;
    QString str = QString(tr("当前次数：%1次")).arg(mCycleCount);
    ui->cycleCountlab->setText(str);
    if(mSelect.empty())//没有选择输出位时，不启动计时器
        return;

    mTimer->start(ui->timespinBox->value()*1000);
}

void MSet_SwCycleWid::on_stopBtn_clicked()
{
    mTimer->stop();

    mCaseCount = 0;
    mCycleCount = 0;//每次停止时，更新循环次数和情况计数状态
    QString str = QString(tr("当前次数：%1次")).arg(mCycleCount);
    ui->cycleCountlab->setText(str);
}

/**
 * @brief 更新情况计数状态，清空textEdit打印信息
 * @brief flag true连续：不停止计时器和不更新循环次数
 * @brief flag false不连续：停止计时器和更新循环次数
 */
void MSet_SwCycleWid::updateCycleCount()
{
    mCaseCount = 0;
    ui->textEdit->clear();
    mCycleCount++;
    QString str = QString(tr("当前次数：%1次")).arg(mCycleCount);
    ui->cycleCountlab->setText(str);
    bool flag = ui->radioButton->isChecked();
    if(!flag)
    {
        if(ui->cycleCountpinBox->value() == mCycleCount)
         {
            mTimer->stop();
            mCycleCount = 0;
        }
    }
}

