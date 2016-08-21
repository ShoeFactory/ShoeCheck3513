#include "entrytotaledittreeitem.h"


EntryTotalEditTreeItem::EntryTotalEditTreeItem(const QVector<QVariant> &data, EntryTotalEditTreeItem *parent)
{
    itemData = data;
    parentItem = parent;
}

EntryTotalEditTreeItem::~EntryTotalEditTreeItem()
{
    qDeleteAll(childItems);
}

EntryTotalEditTreeItem *EntryTotalEditTreeItem::child(int number)
{
    return childItems.value(number); //会帮助检测边界
    if(number>=0 && number< childCount())
        return childItems.at(number); //at不检测边界，自己要确保不越界
}

int EntryTotalEditTreeItem::childCount() const
{
   return childItems.count();
}

int EntryTotalEditTreeItem::columnCount() const
{
    return itemData.count();
}

QVariant EntryTotalEditTreeItem::data(int column) const
{
    return itemData.value(column);
}

bool EntryTotalEditTreeItem::insertChildren(int position, int count, int columns)
{
    if(position < 0 || position > childItems.size())
        return false;

    for(int row = 0; row < count; ++ row)
    {
        QVector<QVariant> data(columns);
        EntryTotalEditTreeItem *item = new EntryTotalEditTreeItem(data, this);
        childItems.insert(position, item);
    }

    return true;
}

bool EntryTotalEditTreeItem::insertColumns(int position, int columns)
{
    if(position < 0 || position > itemData.size())
        return false;

    for(int column = 0; column < columns; ++column )
    {
        itemData.insert(position, QVariant());
    }

    foreach (EntryTotalEditTreeItem *child, childItems) {
        child->insertColumns(position, columns);
    }
    return true;
}

EntryTotalEditTreeItem *EntryTotalEditTreeItem::parent()
{
    return parentItem;
}

bool EntryTotalEditTreeItem::removeChildren(int position, int count)
{
    if(position < 0 || position + count > childItems.size())
        return false;

    for(int row=0; row<count; ++row)
        delete childItems.takeAt(position);

    return true;
}

bool EntryTotalEditTreeItem::removeColumns(int position, int columns)
{
    if(position < 0 || position + columns > itemData.size())
        return false;

    for(int column=0; column< columns; ++column)
        itemData.remove(position);

    foreach (EntryTotalEditTreeItem *child, childItems) {
        child->removeColumns(position, columns);
    }

    return true;
}

bool EntryTotalEditTreeItem::setData(int column, const QVariant &value)
{
    if(column < 0 || column >= itemData.size())
        return false;
    itemData[column] = value;
    return true;
}

int EntryTotalEditTreeItem::childIdInParent() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<EntryTotalEditTreeItem*>(this));
    return 0;
}


