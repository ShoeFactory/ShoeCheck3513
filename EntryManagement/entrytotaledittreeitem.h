#ifndef ENTRYTOTALEDITTREEITEM_H
#define ENTRYTOTALEDITTREEITEM_H

#include <QList>
#include <QVariant>
#include <QVector>

//tree是table的一个特例

class EntryTotalEditTreeItem
{
public:
    ///
    /// \brief EntryTotalEditTreeItem
    /// \param data 每个item可能有很多列
    /// \param parent
    ///
    EntryTotalEditTreeItem(const QVector<QVariant> &data, EntryTotalEditTreeItem *parent=0);
    ~EntryTotalEditTreeItem();

    EntryTotalEditTreeItem *child(int number);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;

    //这些position都是从0开始的， 符合程序员的习惯
    bool insertChildren(int position, int count, int columns);
    bool insertColumns(int position, int columns);

    EntryTotalEditTreeItem *parent();

    bool removeChildren(int position, int count);
    bool removeColumns(int position, int columns);

    bool setData(int column, const QVariant &value);

    int childIdInParent() const;

private:
    QList<EntryTotalEditTreeItem*> childItems;
    QVector<QVariant> itemData;
    EntryTotalEditTreeItem *parentItem;
};

#endif // ENTRYTOTALEDITTREEITEM_H
