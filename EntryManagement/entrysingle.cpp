#include <QtSql>
#include <QtWidgets>

#include "entrysingle.h"

#pragma execution_character_set("utf-8")

EntrySingle::EntrySingle(QWidget *parent)
    : QWidget(parent)
{
    //! [start model view]

    //! 1 shoetype 鞋类型
    tableModel_shoeTypes = new QSqlTableModel(this);
    tableModel_shoeTypes->setTable("shoetypes");
    tableModel_shoeTypes->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableModel_shoeTypes->setHeaderData(0, Qt::Horizontal, tr("编号"));
    tableModel_shoeTypes->setHeaderData(1, Qt::Horizontal, tr("鞋类型"));
    tableModel_shoeTypes->select();

    tableView_shoeTypes = new QTableView(this);
    tableView_shoeTypes->setModel(tableModel_shoeTypes);
    tableView_shoeTypes->setColumnHidden(0, true);
    tableView_shoeTypes->horizontalHeader()->setHidden(true);
    tableView_shoeTypes->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    tableView_shoeTypes->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView_shoeTypes->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView_shoeTypes->setShowGrid(false);
    tableView_shoeTypes->setAlternatingRowColors(true);

    button_shoeType_add = new QPushButton("添加");
    button_shoeType_remove = new QPushButton("移除");

    QGridLayout *grid_shoeType = new QGridLayout;
    grid_shoeType->addWidget(button_shoeType_add, 0, 1, 1, 1);
    grid_shoeType->addWidget(button_shoeType_remove, 0, 3, 1, 1);
    grid_shoeType->addWidget(tableView_shoeTypes, 1, 0, 2, 5);

    QGroupBox *groupbox_shoeType = new QGroupBox("鞋类型");
    groupbox_shoeType->setLayout(grid_shoeType);


    //! 2 errortype 毛病分类
    tableModel_errorTypes = new QSqlTableModel(this);
    tableModel_errorTypes->setTable("errortypes");
    tableModel_errorTypes->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableModel_errorTypes->setHeaderData(0, Qt::Horizontal, tr("编号"));
    tableModel_errorTypes->setHeaderData(1, Qt::Horizontal, tr("毛病分类"));
    tableModel_errorTypes->select();

    tableView_errorTypes = new QTableView(this);
    tableView_errorTypes->setModel(tableModel_errorTypes);
    tableView_errorTypes->setColumnHidden(0, true);
    tableView_errorTypes->horizontalHeader()->setHidden(true);
    tableView_errorTypes->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView_errorTypes->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView_errorTypes->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView_errorTypes->setShowGrid(false);
    tableView_errorTypes->setAlternatingRowColors(true);

    button_errorType_add = new QPushButton("添加");
    button_errorType_remove = new QPushButton("移除");

    QGridLayout *grid_errorType = new QGridLayout;
    grid_errorType->addWidget(button_errorType_add, 0, 1, 1, 1);
    grid_errorType->addWidget(button_errorType_remove, 0, 3, 1, 1);
    grid_errorType->addWidget(tableView_errorTypes, 1, 0, 2, 5);

    QGroupBox *groupbox_errorType = new QGroupBox("毛病分类");
    groupbox_errorType->setLayout(grid_errorType);


    //! 3 errorItems 具体毛病
    tableModel_errorItems = new QSqlTableModel(this);
    tableModel_errorItems->setTable("erroritems");
    tableModel_errorItems->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableModel_errorItems->setHeaderData(0, Qt::Horizontal, tr("编号"));
    tableModel_errorItems->setHeaderData(1, Qt::Horizontal, tr("毛病项目名"));
    tableModel_errorItems->select();

    tableView_errorItems = new QTableView(this);
    tableView_errorItems->setModel(tableModel_errorItems);
    tableView_errorItems->setColumnHidden(0, true);
    tableView_errorItems->horizontalHeader()->setHidden(true);
    tableView_errorItems->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView_errorItems->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView_errorItems->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView_errorItems->setShowGrid(false);
    tableView_errorItems->setAlternatingRowColors(true);


    button_errorItem_add = new QPushButton("添加");
    button_errorItem_remove = new QPushButton("移除");

    QGridLayout *grid_errorItem = new QGridLayout;
    grid_errorItem->addWidget(button_errorItem_add, 0, 1, 1, 1);
    grid_errorItem->addWidget(button_errorItem_remove, 0, 3, 1, 1);
    grid_errorItem->addWidget(tableView_errorItems, 1, 0, 2, 5);

    QGroupBox *groupbox_errorItem = new QGroupBox("毛病项目名");
    groupbox_errorItem->setLayout(grid_errorItem);

    //! 整合
    QHBoxLayout *hbox_views = new QHBoxLayout;
    hbox_views->addWidget(groupbox_shoeType);
    hbox_views->addWidget(groupbox_errorType);
    hbox_views->addWidget(groupbox_errorItem);

    //! [end model view]

    setLayout(hbox_views);

    uniqueShoeTypeID = tableModel_shoeTypes->rowCount();
    uniqueErrorTypeID = tableModel_errorTypes->rowCount();
    uniqueErrorItemID = tableModel_errorItems->rowCount();

    uniqueShoeTypeID = tableModel_shoeTypes->record(uniqueShoeTypeID-1).value(0).toInt();
    uniqueErrorTypeID = tableModel_errorTypes->record(uniqueErrorTypeID-1).value(0).toInt();
    uniqueErrorItemID = tableModel_errorItems->record(uniqueErrorItemID-1).value(0).toInt();

    connect(button_shoeType_add, &QPushButton::clicked, this, &EntrySingle::on_add_shoeType);
    connect(button_errorType_add, &QPushButton::clicked, this, &EntrySingle::on_add_errorType);
    connect(button_errorItem_add, &QPushButton::clicked, this, &EntrySingle::on_add_errorItem);

    connect(button_shoeType_remove, &QPushButton::clicked, this, &EntrySingle::on_remove_shoeType);
    connect(button_errorType_remove, &QPushButton::clicked, this, &EntrySingle::on_remove_errorType);
    connect(button_errorItem_remove, &QPushButton::clicked, this, &EntrySingle::on_remove_errorItem);
}

void EntrySingle::on_add_shoeType()
{
    QSqlField f1("id", QVariant::Int);
    QSqlField f2("name", QVariant::String);
    f1.setValue(QVariant().fromValue(getUniqueShoeTypeId()));
    f2.setValue(QVariant(QString()));

    QSqlRecord record;
    record.append(f1);
    record.append(f2);

    bool inserted = tableModel_shoeTypes->insertRecord(-1, record);
    if(!inserted)
    {
        QMessageBox::critical(this, "添加失败", "向鞋类型中添加新品失败");
    }
}

void EntrySingle::on_add_errorType()
{
    QSqlField f1("id", QVariant::Int);
    QSqlField f2("name", QVariant::String);
    f1.setValue(QVariant().fromValue(getUniqueErrorTypeId()));
    f2.setValue(QVariant(QString()));

    QSqlRecord record;
    record.append(f1);
    record.append(f2);

    bool inserted = tableModel_errorTypes->insertRecord(-1, record);
    if(!inserted)
    {
        QMessageBox::critical(this, "添加失败", "向毛病类型中添加失败");
    }
}

void EntrySingle::on_add_errorItem()
{
    QSqlField f1("id", QVariant::Int);
    QSqlField f2("name", QVariant::String);
    f1.setValue(QVariant().fromValue(getUniqueErrorItemId()));
    f2.setValue(QVariant(QString()));

    QSqlRecord record;
    record.append(f1);
    record.append(f2);

    bool inserted = tableModel_errorItems->insertRecord(-1, record);
    if(!inserted)
    {
        QMessageBox::critical(this, "添加失败", "向毛病项目中添加失败");
    }
}

void EntrySingle::on_remove_shoeType()
{
    QModelIndexList selection = tableView_shoeTypes->selectionModel()->selectedRows(0);

    if (!selection.empty())
    {
        QModelIndex idIndex = selection.at(0);
        tableModel_shoeTypes->removeRow(idIndex.row());
    }
    else
    {
        QMessageBox::information(this, tr("Delete shoe type"),
                                 tr("Select the shoe type you want to delete."));
    }
}

void EntrySingle::on_remove_errorType()
{
    QModelIndexList selection = tableView_errorTypes->selectionModel()->selectedRows(0);

    if (!selection.empty())
    {
        QModelIndex idIndex = selection.at(0);
        tableModel_errorTypes->removeRow(idIndex.row());
    }
    else
    {
        QMessageBox::information(this, tr("Delete error type"),
                                 tr("Select the error type you want to delete."));
    }
}

void EntrySingle::on_remove_errorItem()
{
    QModelIndexList selection = tableView_errorItems->selectionModel()->selectedRows(0);

    if (!selection.empty())
    {
        QModelIndex idIndex = selection.at(0);
        tableModel_errorItems->removeRow(idIndex.row());
    }
    else
    {
        QMessageBox::information(this, tr("Delete error item"),
                                 tr("Select the error item you want to delete."));
    }
}


void EntrySingle::on_cancel()
{
    tableModel_shoeTypes->revertAll();
    tableModel_errorTypes->revertAll();
    tableModel_errorItems->revertAll();
}

void EntrySingle::on_apply()
{

    tableModel_shoeTypes->database().transaction();
    if (tableModel_shoeTypes->submitAll()) {
        tableModel_shoeTypes->database().commit();
    } else {
        tableModel_shoeTypes->database().rollback();
        QMessageBox::warning(this, tr("Error commit"),
                             tr("The database shoeTypes reported an error: %1")
                             .arg(tableModel_shoeTypes->lastError().text()));
    }

    tableModel_errorTypes->database().transaction();
    if (tableModel_errorTypes->submitAll()) {
        tableModel_errorTypes->database().commit();
    } else {
        tableModel_errorTypes->database().rollback();
        QMessageBox::warning(this, tr("Error commit"),
                             tr("The database errorTypes reported an error: %1")
                             .arg(tableModel_errorTypes->lastError().text()));
    }

    tableModel_errorItems->database().transaction();
    if (tableModel_errorItems->submitAll()) {
        tableModel_errorItems->database().commit();
    } else {
        tableModel_errorItems->database().rollback();
        QMessageBox::warning(this, tr("Error commit"),
                             tr("The database errorItems reported an error: %1")
                             .arg(tableModel_errorItems->lastError().text()));
    }

}

int EntrySingle::getUniqueShoeTypeId()
{
    return ++uniqueShoeTypeID;
}

int EntrySingle::getUniqueErrorTypeId()
{
    return ++uniqueErrorTypeID;
}

int EntrySingle::getUniqueErrorItemId()
{
    return ++uniqueErrorItemID;
}

