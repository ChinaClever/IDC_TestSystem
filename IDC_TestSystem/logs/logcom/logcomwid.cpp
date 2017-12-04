#include "logcomwid.h"
#include "ui_logcomwid.h"
#include "common.h"
#include "log_exportdlg.h"

LogComWid::LogComWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogComWid)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
    QTimer::singleShot(100,this,SLOT(initFunSLot())); //延时初始化   
}

LogComWid::~LogComWid()
{
    delete ui;
}

void LogComWid::setGroupBoxTitle(const QString &title)
{
    ui->groupBox->setTitle(title);
}

void LogComWid::setStretch()
{

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


void LogComWid::initFunSLot()
{
    QString name =  getDb()->tableName();

    ui->tableView->setSortingEnabled(true);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //禁用编辑功能

    model = new SqlTableModel(ui->tableView);
    ui->tableView->setModel(model->model);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    connect(ui->tableView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(doubleSlot(QModelIndex)));

    initTable();
    mDateWidget = new LOG_DateWidget(ui->dateWid);
    mDateWidget->setTable(name);
    connect(mDateWidget,SIGNAL(selectedSig(QString)), model,SLOT(queryFilter(QString)));

    initBtnBar();
}

void LogComWid::initBtnBar()
{
    mBtnBar = new LogBtnBar(ui->widget);
    connect(mBtnBar,SIGNAL(querySig(QString)),model,SLOT(queryFilter(QString)));
    connect(mBtnBar,SIGNAL(clearSig()),this,SLOT(clearTableSlot()));
    connect(mBtnBar,SIGNAL(refreshSig()),this,SLOT(refreshSlot()));
    connect(mBtnBar,SIGNAL(refreshSig()),mDateWidget,SLOT(updateSlot()));
    connect(mBtnBar,SIGNAL(exportSig()),this,SLOT(exportSlot()));
}



bool LogComWid::refreshTable(const QString &table)
{
    bool ret = model->refreshTable(table);
    if(ret) {
        ui->tableView->sortByColumn(0, Qt::DescendingOrder); // 降序排列
        ui->tableView->setColumnHidden(0, true);
    }
    return  ret;
}


void LogComWid::refreshSlot()
{
    initTable();
}


void LogComWid::clearTableSlot()
{
    model->model->setTable("markingtable");
    BasicSql* db = getDb();
    db->clear();
    db->createTable();
    initTable();
    //    if(model->removeRow(0))
    //        QTimer::singleShot(10,this,SLOT(clearTableSlot()));
}


void LogComWid::doubleSlot(QModelIndex)
{
    QString str = tr("是否删除这条纪录?");
    QuMsgBox box(this, str);
    bool ret = box.Exec();
    if(ret)
    {
        int curRow = ui->tableView->currentIndex().row();
        model->removeRow(curRow);
    }
}

void LogComWid::exportSlot()
{
    LOG_ExportDlg dlg(this);
    QString name = getDb()->tableName();
    dlg.set(name, mHeadList, mTableTile);

    QDate start, end;
    mBtnBar->getDate(start, end);
    dlg.setDate(start, end);
    dlg.exec();
}
