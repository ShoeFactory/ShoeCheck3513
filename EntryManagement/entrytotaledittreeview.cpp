#include "entrytotaledittreeview.h"

EntryTotalEditTreeView::EntryTotalEditTreeView(QWidget *parent)
    :QTreeView(parent)
{
    setEditTriggers(QTreeView::NoEditTriggers);
}
