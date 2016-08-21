#ifndef ENTRYTOTALEDITTREEMODEL_H
#define ENTRYTOTALEDITTREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QSqlRelationalTableModel>

#include "entrytotaledittreeitem.h"

class EntryTotalEditTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    EntryTotalEditTreeModel(const QStringList &headers, QObject *parent = 0);
    ~EntryTotalEditTreeModel();

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &child) const Q_DECL_OVERRIDE;

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent= QModelIndex()) const Q_DECL_OVERRIDE;

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role) Q_DECL_OVERRIDE;

    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

    bool insertColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    bool removeColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    bool insertRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    bool removeRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;

    QSqlRelationalTableModel *getTableModel();
    bool insertRecordToTree(QString shoeTypeStr, QString errorTypeStr, QString errorItemStr);
    bool insertRecordToTable(int id, QString shoeTypeStr, QString errorTypeStr, QString errorItemStr);

public:
    bool wangxk_save();
    void select();

private:
    //把这个table存放在rootItem这颗树上
    void setupModelData();
    EntryTotalEditTreeItem *getItem(const QModelIndex &index) const;

    //从ralationaltablemodel 给 rootitem代表的树上 转换
    EntryTotalEditTreeItem *rootItem;
    QSqlRelationalTableModel *relationalTableModel;

    void convertTableToTree();
    void commitTreeUsingTable();
};

#endif // ENTRYTOTALEDITTREEMODEL_H
