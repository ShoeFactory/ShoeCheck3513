#include "entrytotaledittreemodel.h"
#include <QSqlRecord>
#include <QSqlField>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlTableModel>
#include <QDebug>

#pragma execution_character_set("utf-8")

EntryTotalEditTreeModel::EntryTotalEditTreeModel(const QStringList &headers, QObject *parent)
    :QAbstractItemModel(parent)
{
    ///生成树
    //设置header root的data就是view的header
    QVector<QVariant> rootData;
    foreach (QString header, headers) {
        rootData << header;
    }
    rootItem = new EntryTotalEditTreeItem(rootData);

    ///生成table
    relationalTableModel = new QSqlRelationalTableModel(this);
    relationalTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    relationalTableModel->setTable("detectiontotal");
    relationalTableModel->setRelation(1, QSqlRelation("shoetypes", "id", "name"));
    relationalTableModel->setRelation(2, QSqlRelation("errortypes", "id", "name"));
    relationalTableModel->setRelation(3, QSqlRelation("erroritems", "id", "name"));
    //把数据库中名为table的表格 拿来放在这里
    convertTableToTree();
}

EntryTotalEditTreeModel::~EntryTotalEditTreeModel()
{
    delete rootItem;
}

QModelIndex EntryTotalEditTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    //只允许第0列能有有子项
    if(parent.isValid() && parent.column() != 0)
    {
        return QModelIndex();
    }

    EntryTotalEditTreeItem *item = getItem(parent);

    EntryTotalEditTreeItem *childItem = item->child(row);
    if(childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex EntryTotalEditTreeModel::parent(const QModelIndex &child) const
{
    if(!child.isValid())
        return QModelIndex();

    EntryTotalEditTreeItem *childItem = getItem(child);
    EntryTotalEditTreeItem *parentItem = childItem->parent();

    if(parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->childIdInParent(), 0, parentItem);
}

int EntryTotalEditTreeModel::rowCount(const QModelIndex &parent) const
{
    EntryTotalEditTreeItem *parentItem = getItem(parent);
    return parentItem->childCount();
}

int EntryTotalEditTreeModel::columnCount(const QModelIndex & /*parent*/) const
{
    return rootItem->columnCount();
}

QVariant EntryTotalEditTreeModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    if(role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();


    EntryTotalEditTreeItem *item = getItem(index);

    return item->data(index.column());
}

QVariant EntryTotalEditTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

bool EntryTotalEditTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role != Qt::EditRole)
        return false;

    EntryTotalEditTreeItem *item = getItem(index);
    if(item)
    {
        bool result = item->setData(index.column(), value);
        if(result)
            emit dataChanged(index, index);
        return result;
    }

    return false;
}

bool EntryTotalEditTreeModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if(role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    bool result = rootItem->setData(section, value);

    if(result)
        emit headerDataChanged(orientation, section, section);

    return result;
}

Qt::ItemFlags EntryTotalEditTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

bool EntryTotalEditTreeModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginInsertColumns(parent, position, position + columns - 1);
    success = rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool EntryTotalEditTreeModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginRemoveColumns(parent, position, position + columns -1);
    success = rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;

}

bool EntryTotalEditTreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    EntryTotalEditTreeItem *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildren(position, rows, rootItem->columnCount());
    endInsertRows();

    return success;
}

bool EntryTotalEditTreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    EntryTotalEditTreeItem *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

QSqlRelationalTableModel *EntryTotalEditTreeModel::getTableModel()
{
    return relationalTableModel;
}

void EntryTotalEditTreeModel::setupModelData()
{
    QVector<QVariant> columnData;
    columnData << QVariant(QString("aaa"))
               << QVariant(QString("bbb"));

    EntryTotalEditTreeItem *parent = rootItem;
    parent->insertChildren(parent->childCount(), 1, rootItem->columnCount());
    for (int column = 0; column < columnData.size(); ++column)
        parent->child(parent->childCount() - 1)->setData(column, columnData[column]);

    parent = parent->child(0);
    parent->insertChildren(parent->childCount(), 1, rootItem->columnCount());
    for (int column = 0; column < columnData.size(); ++column)
        parent->child(parent->childCount() - 1)->setData(column, columnData[column]);
}

EntryTotalEditTreeItem *EntryTotalEditTreeModel::getItem(const QModelIndex &index) const
{
    if(index.isValid())
    {
        EntryTotalEditTreeItem *item = static_cast<EntryTotalEditTreeItem*>(index.internalPointer());
        if(item)
            return item;
    }
    return rootItem;
}


void EntryTotalEditTreeModel::convertTableToTree()
{
    //先清空
    int childNum = rootItem->childCount();
    if(childNum > 0)
    {
        removeRows(0, childNum, QModelIndex());
    }

    //再填充
    relationalTableModel->select();

    int tableRowCount = relationalTableModel->rowCount();
    for(int tableRow=0; tableRow<tableRowCount; tableRow++)
    {
        QSqlRecord record = relationalTableModel->record(tableRow);

        QString shoeType = record.value(1).toString();
        QString errorType = record.value(2).toString();
        QString errorItem = record.value(3).toString();

        insertRecordToTree(shoeType, errorType, errorItem);
    }
}

bool EntryTotalEditTreeModel::insertRecordToTree(QString shoeTypeStr, QString errorTypeStr, QString errorItemStr)
{
    //处理shoeType
    EntryTotalEditTreeItem *treeItem_shoeType = NULL;
    QModelIndex shoeTypeIndex;

    for(int i=0; i<rootItem->childCount(); i++)
    {
        EntryTotalEditTreeItem *treeItem_temp = rootItem->child(i);
        if(treeItem_temp->data(0).toString() == shoeTypeStr)
        {
            treeItem_shoeType = treeItem_temp;
            shoeTypeIndex = createIndex(i, 0, treeItem_shoeType);
        }
    }
    if(treeItem_shoeType == NULL)
    {
        QVector<QVariant> columnData;
        columnData << QVariant(shoeTypeStr);

        insertRow(rootItem->childCount() ,QModelIndex() );
        treeItem_shoeType = rootItem->child(rootItem->childCount()-1);
        shoeTypeIndex = createIndex(rootItem->childCount()-1, 0, treeItem_shoeType);
        for (int column = 0; column < columnData.size(); ++column)
        {
            setData(shoeTypeIndex, columnData[column], Qt::EditRole);
        }
    }

    //处理errortype
    EntryTotalEditTreeItem *treeItem_errorType = NULL;
    QModelIndex errorTypeIndex ;

    for(int i=0; i<treeItem_shoeType->childCount(); i++)
    {
        EntryTotalEditTreeItem *treeItem_temp = treeItem_shoeType->child(i);
        if(treeItem_temp->data(0).toString() == errorTypeStr)
        {
            treeItem_errorType = treeItem_temp;
            errorTypeIndex = createIndex(i, 0, treeItem_errorType);
        }
    }
    if(treeItem_errorType == NULL)
    {
        QVector<QVariant> columnData;
        columnData << QVariant(errorTypeStr);

        insertRow(treeItem_shoeType->childCount() ,shoeTypeIndex);
        treeItem_errorType = treeItem_shoeType->child(treeItem_shoeType->childCount()-1);
        errorTypeIndex = createIndex(treeItem_shoeType->childCount()-1, 0, treeItem_errorType);
        for (int column = 0; column < columnData.size(); ++column)
        {
            setData(errorTypeIndex, columnData[column], Qt::EditRole);
        }
    }

    //处理erroritem
    EntryTotalEditTreeItem *treeItem_errorItem = NULL;
    QModelIndex errorItemIndex ;

    for(int i=0; i<treeItem_errorType->childCount(); i++)
    {
        EntryTotalEditTreeItem *treeItem_temp = treeItem_errorType->child(i);
        if(treeItem_temp->data(0).toString() == errorItemStr)
        {
            treeItem_errorItem = treeItem_temp;
            return false;
        }
    }
    if(treeItem_errorItem == NULL)
    {
        QVector<QVariant> columnData;
        columnData << QVariant(errorItemStr);

        insertRow(treeItem_errorType->childCount() ,errorTypeIndex);
        treeItem_errorItem = treeItem_errorType->child(treeItem_errorType->childCount()-1);
        errorItemIndex = createIndex(treeItem_errorType->childCount()-1, 0, treeItem_errorItem);
        for (int column = 0; column < columnData.size(); ++column)
        {
            setData(errorItemIndex, columnData[column], Qt::EditRole);
        }
    }

    return true;
}

bool EntryTotalEditTreeModel::insertRecordToTable(int id, QString shoeTypeStr, QString errorTypeStr, QString errorItemStr)
{
        QSqlTableModel *shoeTypeModel = relationalTableModel->relationModel(1);
        QSqlTableModel *errorTypeModel = relationalTableModel->relationModel(2);
        QSqlTableModel *errorItemModel = relationalTableModel->relationModel(3);

        int shoeTyperow = 0;
        int errorTyperow = 0;
        int errorItemRow = 0;

        while (shoeTyperow < shoeTypeModel->rowCount()) {
            QSqlRecord record = shoeTypeModel->record(shoeTyperow);
            if (record.value("name") == shoeTypeStr)
            {
                shoeTyperow = record.value("id").toInt();
                break;
            }
            else
                shoeTyperow++;
        }

        while (errorTyperow < errorTypeModel->rowCount()) {
            QSqlRecord record = errorTypeModel->record(errorTyperow);
            if (record.value("name") == errorTypeStr)
            {
                errorTyperow = record.value("id").toInt();
                break;
            }
            else
                errorTyperow++;
        }

        while (errorItemRow < errorItemModel->rowCount()) {
            QSqlRecord record = errorItemModel->record(errorItemRow);
            if (record.value("name") == errorItemStr)
            {
                errorItemRow = record.value("id").toInt();
                break;
            }
            else
                errorItemRow++;
        }

        QSqlField f1("id", QVariant::Int);
        QSqlField f2("shoetypeid", QVariant::Int);
        QSqlField f3("errortypeid", QVariant::Int);
        QSqlField f4("erroritemid", QVariant::Int);

        f1.setValue(QVariant().fromValue(id));
        f2.setValue(QVariant().fromValue(shoeTyperow));
        f3.setValue(QVariant().fromValue(errorTyperow));
        f4.setValue(QVariant().fromValue(errorItemRow));

        QSqlRecord record;
        record.append(f1);
        record.append(f2);
        record.append(f3);
        record.append(f4);

        bool inserted = relationalTableModel->insertRecord(-1, record);
        if(!inserted)
        {
            QMessageBox::critical(0, "添加失败", "向毛病数据库中添加失败");
            return false;
        }
        else
        {
            return true;
        }
}

bool EntryTotalEditTreeModel::wangxk_save()
{
    relationalTableModel->removeRows(0, relationalTableModel->rowCount());

    //生成重新生成 tablemodel
    int idInTableModel = 1;
    for(int shoeTypeID = 0; shoeTypeID < rootItem->childCount(); shoeTypeID++)
    {
        //处理每一种鞋子
        EntryTotalEditTreeItem *shoeTypeItem = rootItem->child(shoeTypeID);
        QString str_shoeType  = shoeTypeItem->data(0).toString();
        for(int errorTypeId = 0; errorTypeId < shoeTypeItem->childCount(); errorTypeId++)
        {
            //处理每一种错误类型
            EntryTotalEditTreeItem *errorTypeItem = shoeTypeItem->child(errorTypeId);
            QString str_errorType = errorTypeItem->data(0).toString();

            for(int errorItemId = 0; errorItemId < errorTypeItem->childCount(); errorItemId++)
            {
                //处理每一种具体错误
                EntryTotalEditTreeItem *errorItemItem = errorTypeItem->child(errorItemId);
                QString str_errorItem = errorItemItem->data(0).toString();

                insertRecordToTable(idInTableModel++, str_shoeType, str_errorType, str_errorItem);
            }
        }
    }

    int modelrowcount =  relationalTableModel->rowCount();
    //提交 tablemodel
    relationalTableModel->database().transaction();
    if (relationalTableModel->submitAll()) {
        relationalTableModel->database().commit();
    } else {
        relationalTableModel->database().rollback();
        QMessageBox::warning(0, tr("Error commit"),
                             tr("The database detectiontotal reported an error: %1")
                             .arg(relationalTableModel->lastError().text()));
    }

    return true;
}

void EntryTotalEditTreeModel::select()
{
    convertTableToTree();
}
