#include "entrytotal.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QItemSelectionModel>

#include "entrytotaladddialog.h"

#pragma execution_character_set("utf-8")

EntryTotal::EntryTotal(QWidget *parent) : QWidget(parent)
{
    edit_treeView = new EntryTotalEditTreeView;
    QStringList modelHeaders = QStringList()<< QString("这里的header看不见");
    edit_treeModel = new EntryTotalEditTreeModel(modelHeaders, this);
    edit_treeView->setModel(edit_treeModel);
    edit_treeView->header()->setHidden(true);

    connect(edit_treeView->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &,
                                    const QItemSelection &)),
            this, SLOT(updateActions()));

    button_remove = new QPushButton("删除项目");
    button_add = new QPushButton("添加项目");

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(button_add);
    buttonLayout->addWidget(button_remove);
    buttonLayout->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(edit_treeView);
    mainLayout->addLayout(buttonLayout);


    connect(button_add, &QPushButton::clicked, this, &EntryTotal::add_item);
    connect(button_remove, &QPushButton::clicked, this, &EntryTotal::remove_item);
}

void EntryTotal::on_cancel()
{
    ;
}

void EntryTotal::on_apply()
{
    edit_treeModel->wangxk_save();
}

void EntryTotal::add_item()
{
    QStringList currentSelected;

    QModelIndex index = edit_treeView->selectionModel()->currentIndex();
    if(index.parent().isValid())
    {
        if(index.parent().parent().isValid())
        {
            //当前选中erroritem
            currentSelected << edit_treeModel->data(index.parent().parent(), Qt::DisplayRole).toString()
                            << edit_treeModel->data(index.parent(), Qt::DisplayRole).toString()
                            << QString();
        }
        else
        {
            //当前选中errortype
            currentSelected << edit_treeModel->data(index.parent(), Qt::DisplayRole).toString()
                            << edit_treeModel->data(index, Qt::DisplayRole).toString()
                            << QString();
        }
    }
    else
    {
        //当前选中shoetype
        currentSelected << edit_treeModel->data(index, Qt::DisplayRole).toString()
                        << QString()
                        << QString();
    }

    EntryTotalAddDialog *dialog = new EntryTotalAddDialog(edit_treeModel, currentSelected, this);
    if(QDialog::Accepted == dialog->exec())
    {
        ;
    }

}

void EntryTotal::remove_item()
{
    QModelIndex index = edit_treeView->selectionModel()->currentIndex();
    QAbstractItemModel *model = edit_treeView->model();
    if (model->removeRow(index.row(), index.parent()))
        updateActions();
}

void EntryTotal::updateActions()
{
    QItemSelectionModel *selectionModel = edit_treeView->selectionModel();
    bool hasSelection = !selectionModel->selection().isEmpty();
    if(hasSelection)
    {
        button_remove->setEnabled(true);
    }
    else
    {
        button_remove->setEnabled(false);
    }
}

