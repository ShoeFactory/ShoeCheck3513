#ifndef ENTRYTOTAL_H
#define ENTRYTOTAL_H

#include <QWidget>
#include <QTreeView>
#include <QPushButton>

#include "entrytotaledittreeview.h"
#include "entrytotaledittreemodel.h"

class EntryTotal : public QWidget
{
    Q_OBJECT
public:
    explicit EntryTotal(QWidget *parent = 0);
    void on_cancel();
    void on_apply();


private slots:
    void add_item();
    void remove_item();

private:
    EntryTotalEditTreeView *edit_treeView;
    EntryTotalEditTreeModel *edit_treeModel;

    QPushButton *button_add;
    QPushButton *button_remove;


private slots:
    void updateActions();
};

#endif // ENTRYTOTAL_H
